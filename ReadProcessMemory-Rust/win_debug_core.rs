use std::os::raw::c_void;

#[repr(C)]
pub struct DebugEvent {
    pub event_code: u32,
    pub process_id: u32,
    pub thread_id: u32,
    pub u: [u8; 160], // ユニオンの簡易的なバッファ（実際はより詳細に定義可能）
}

extern "C" {
    fn AttachDebugger(dw_process_id: u32) -> bool;
    fn DetachDebugger(dw_process_id: u32) -> bool;
    fn WaitForDebugEventSafe(lp_debug_event: *mut DebugEvent, dw_milliseconds: u32) -> bool;
    fn ContinueDebug(dw_process_id: u32, dw_thread_id: u32, dw_continue_status: u32) -> bool;
}

pub struct DebugSession {
    pid: u32,
}

impl DebugSession {
    pub fn attach(pid: u32) -> Result<Self, String> {
        unsafe {
            if AttachDebugger(pid) {
                Ok(DebugSession { pid })
            } else {
                Err(format!("Could not attach to process {}", pid))
            }
        }
    }

    pub fn wait_for_event(&self, timeout_ms: u32) -> Option<DebugEvent> {
        let mut event = std::mem::maybe_uninit::<DebugEvent>();
        unsafe {
            if WaitForDebugEventSafe(event.as_mut_ptr(), timeout_ms) {
                Some(event.assume_init())
            } else {
                None
            }
        }
    }

    pub fn continue_execution(&self, tid: u32, status: u32) -> bool {
        unsafe { ContinueDebug(self.pid, tid, status) }
    }
}

// VSのように、セッションが終わったら自動でデタッチする
impl Drop for DebugSession {
    fn drop(&mut self) {
        unsafe { DetachDebugger(self.pid); }
    }
}
