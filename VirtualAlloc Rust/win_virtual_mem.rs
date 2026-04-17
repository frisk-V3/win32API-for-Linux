use std::ptr::NonNull;
use std::ops::{Deref, DerefMut};
use windows::Win32::System::Memory::{
    VirtualAlloc, VirtualFree, VirtualProtect, MEM_COMMIT, MEM_RESERVE, 
    PAGE_READWRITE, PAGE_EXECUTE_READ, MEM_RELEASE, PAGE_PROTECTION_FLAGS
};
use windows::Win32::System::SystemInformation::{GetSystemInfo, SYSTEM_INFO};

/// ページサイズに基づいた、Windowsネイティブな仮想メモリ管理バッファ
pub struct VirtualBuffer {
    ptr: NonNull<std::ffi::c_void>,
    size: usize,
    capacity: usize, // 実際にシステムが確保したページアライメント済みのサイズ
}

impl VirtualBuffer {
    /// 指定されたサイズ以上のメモリを確保する。
    /// 内部的にシステムのページサイズ（通常4KB）の倍数に切り上げられる。
    pub fn new(requested_size: usize) -> Result<Self, String> {
        if requested_size == 0 {
            return Err("Size must be greater than zero".to_string());
        }

        unsafe {
            // システムのページサイズを取得
            let mut sys_info = SYSTEM_INFO::default();
            GetSystemInfo(&mut sys_info);
            let page_size = sys_info.dwPageSize as usize;

            // リクエストサイズをページサイズの倍数に切り上げる (Alignment)
            let aligned_size = (requested_size + page_size - 1) & !(page_size - 1);

            let addr = VirtualAlloc(
                None,
                aligned_size,
                MEM_COMMIT | MEM_RESERVE,
                PAGE_READWRITE,
            );

            if addr.is_null() {
                return Err("VirtualAlloc failed to reserve memory".to_string());
            }

            Ok(Self {
                ptr: NonNull::new_unchecked(addr),
                size: requested_size,
                capacity: aligned_size,
            })
        }
    }

    /// メモリの保護状態を「実行可能・読み取り専用」に変更する（JITコンパイラ等で利用）
    pub fn make_executable(&self) -> Result<(), String> {
        unsafe {
            let mut old_protect = PAGE_PROTECTION_FLAGS::default();
            VirtualProtect(
                self.ptr.as_ptr(),
                self.capacity,
                PAGE_EXECUTE_READ,
                &mut old_protect,
            ).map_err(|e| format!("Failed to change memory protection: {}", e))?;
            Ok(())
        }
    }

    /// 実際にOSから確保されているキャパシティ（ページサイズ境界）を返す
    pub fn capacity(&self) -> usize {
        self.capacity
    }

    /// 安全なスライスへの変換
    pub fn as_slice(&self) -> &[u8] {
        unsafe { std::slice::from_raw_parts(self.ptr.as_ptr() as *const u8, self.size) }
    }

    /// 安全な可変スライスへの変換
    pub fn as_slice_mut(&mut self) -> &mut [u8] {
        unsafe { std::slice::from_raw_parts_mut(self.ptr.as_ptr() as *mut u8, self.size) }
    }

    /// デバッグ用の生ポインタ取得
    pub fn raw_ptr(&self) -> *mut std::ffi::c_void {
        self.ptr.as_ptr()
    }
}

// Derefトレイトの実装により、スライスのように振る舞えるようにする
impl Deref for VirtualBuffer {
    type Target = [u8];
    fn deref(&self) -> &Self::Target {
        self.as_slice()
    }
}

impl DerefMut for VirtualBuffer {
    fn deref_mut(&mut self) -> &mut Self::Target {
        self.as_slice_mut()
    }
}

// マルチスレッド対応
unsafe impl Send for VirtualBuffer {}
unsafe impl Sync for VirtualBuffer {}

impl Drop for VirtualBuffer {
    fn drop(&mut self) {
        unsafe {
            // 第2引数が 0 かつ MEM_RELEASE は Win32 API の厳格なルール
            let result = VirtualFree(self.ptr.as_ptr(), 0, MEM_RELEASE);
            if result.is_err() {
                eprintln!("Warning: Failed to release virtual memory.");
            } else {
                println!(
                    "Memory successfully released. Address: {:?}, Aligned Size: {} bytes", 
                    self.ptr, 
                    self.capacity
                );
            }
        }
    }
}

fn main() -> Result<(), String> {
    // 1. バッファの確保（リクエストは100バイトだが、内部で4096バイト程度確保される）
    let mut buffer = VirtualBuffer::new(100)?;
    
    // 2. 書き込み（DerefMutによりスライスとして扱える）
    buffer[0] = 0x90; // NOP命令
    buffer[1] = 0xC3; // RET命令
    
    println!("Buffer created with capacity: {} bytes", buffer.capacity());
    println!("First two bytes: [0x{:x}, 0x{:x}]", buffer[0], buffer[1]);

    // 3. 実行可能フラグの付与
    buffer.make_executable()?;
    println!("Memory protection changed to PAGE_EXECUTE_READ.");

    Ok(())
}
