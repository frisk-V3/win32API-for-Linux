use std::collections::HashMap;
use std::ffi::c_void;

// --- 構造体定義 ---

pub struct Breakpoint {
    pub address: usize,
    pub original_byte: u8,
}

pub struct BreakpointManager {
    // アドレスをキーにブレークポイント情報を保持
    breakpoints: HashMap<usize, Breakpoint>,
}

// --- 実装 ---

impl BreakpointManager {
    pub fn new() -> Self {
        Self { breakpoints: HashMap::new() }
    }

    /// VSの「赤丸」：指定アドレスに 0xCC (INT 3) を書き込む
    pub fn add_breakpoint(&mut self, h_process: *mut c_void, address: usize) -> Result<(), String> {
        let mut old_byte: u8 = 0;
        unsafe {
            // C++側で WriteProcessMemory(h_process, address, &0xCC, 1, &old_byte) する想定
            if super::win_breakpoint::SetSoftwareBreakpoint(h_process, address as *mut _, &mut old_byte) {
                self.breakpoints.insert(address, Breakpoint { address, original_byte: old_byte });
                Ok(())
            } else {
                Err(format!("Could not set BP at 0x{:X}", address))
            }
        }
    }

    /// ブレークポイントの解除：元の命令バイトを書き戻す
    pub fn remove_breakpoint(&mut self, h_process: *mut c_void, address: usize) -> Result<(), String> {
        if let Some(bp) = self.breakpoints.remove(&address) {
            unsafe {
                if super::win_breakpoint::RestoreOriginalByte(h_process, address as *mut _, bp.original_byte) {
                    return Ok(());
                }
            }
        }
        Err("Breakpoint not found or restore failed".to_string())
    }

    /// デバッグイベント発生時に呼ばれる「ヒット時処理」の核心
    /// 引数: プロセスハンドル, スレッドハンドル
    pub fn handle_breakpoint_hit(&mut self, h_process: *mut c_void, h_thread: *mut c_void) -> Option<usize> {
        unsafe {
            let mut context = std::mem::zeroed::<super::win_breakpoint::CONTEXT>();
            context.ContextFlags = 0x10001; // CONTEXT_CONTROL

            // 1. 現在のレジスタ（RIP/EIP）を取得
            super::win_breakpoint::GetThreadContext(h_thread, &mut context);

            // 2. INT 3 実行後は命令ポインタが 1 進んでいるので戻す
            let hit_addr = (context.Rip - 1) as usize;

            if let Some(bp) = self.breakpoints.get(&hit_addr) {
                // 命令ポインタを 0xCC の位置に巻き戻す
                context.Rip -= 1;
                
                // 元の命令をメモリに書き戻す（これで次の一歩が踏める）
                super::win_breakpoint::RestoreOriginalByte(h_process, hit_addr as *mut _, bp.original_byte);

                // 3. トラップフラグ(TF)を立てて「1命令だけ実行」モードにする
                // これにより、次の命令実行後に EXCEPTION_SINGLE_STEP が発生する
                context.EFlags |= 0x100; 

                // コンテキストをスレッドに反映
                super::win_breakpoint::SetThreadContext(h_thread, &context);

                return Some(hit_addr);
            }
        }
        None
    }

    /// シングルステップ完了後、再び 0xCC を書き込んでブレークポイントを再有効化する
    pub fn re-enable_breakpoint(&mut self, h_process: *mut c_void, address: usize) {
        let _ = self.add_breakpoint(h_process, address);
    }
}

