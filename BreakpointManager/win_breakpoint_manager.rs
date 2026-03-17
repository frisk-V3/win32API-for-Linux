use std::collections::HashMap;

pub struct Breakpoint {
    pub address: usize,
    pub original_byte: u8,
    pub enabled: bool,
}

pub struct BreakpointManager {
    // アドレスをキーにしてBP情報を保持
    breakpoints: HashMap<usize, Breakpoint>,
}

impl BreakpointManager {
    pub fn new() -> Self {
        Self { breakpoints: HashMap::new() }
    }

    // VSの「赤丸」を付ける操作に相当
    pub fn add_breakpoint(&mut self, h_process: *mut std::ffi::c_void, address: usize) -> Result<(), String> {
        let mut old_byte: u8 = 0;
        unsafe {
            // 前に作った C++ の SetSoftwareBreakpoint を呼ぶ
            if super::win_breakpoint::SetSoftwareBreakpoint(h_process, address as *mut _, &mut old_byte) {
                self.breakpoints.insert(address, Breakpoint {
                    address,
                    original_byte: old_byte,
                    enabled: true,
                });
                Ok(())
            } else {
                Err("Could not set breakpoint".to_string())
            }
        }
    }
}
