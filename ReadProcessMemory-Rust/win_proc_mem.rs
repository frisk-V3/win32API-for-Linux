use std::ptr;
use std::os::raw::c_void;

#[repr(C)]
pub struct MemoryBasicInformation {
    pub base_address: *mut c_void,
    pub allocation_base: *mut c_void,
    pub allocation_protect: u32,
    pub region_size: usize,
    pub state: u32,
    pub protect: u32,
    pub type_info: u32,
}

extern "C" {
    fn ReadProcessMemorySafe(h_process: *mut c_void, address: *const c_void, buffer: *mut c_void, size: usize, bytes_read: *mut usize) -> bool;
    fn WriteProcessMemorySafe(h_process: *mut c_void, address: *mut c_void, buffer: *const c_void, size: usize, bytes_written: *mut usize) -> bool;
}

pub struct ProcessHandle(pub *mut c_void);

impl ProcessHandle {
    pub fn read_memory(&self, address: usize, size: usize) -> Result<Vec<u8>, String> {
        let mut buffer = vec![0u8; size];
        let mut bytes_read = 0;
        unsafe {
            if ReadProcessMemorySafe(self.0, address as *const c_void, buffer.as_mut_ptr() as *mut c_void, size, &mut bytes_read) {
                buffer.truncate(bytes_read);
                Ok(buffer)
            } else {
                Err("Failed to read process memory".to_string())
            }
        }
    }

    pub fn write_memory(&self, address: usize, data: &[u8]) -> Result<usize, String> {
        let mut bytes_written = 0;
        unsafe {
            if WriteProcessMemorySafe(self.0, address as *mut c_void, data.as_ptr() as *const c_void, data.len(), &mut bytes_written) {
                Ok(bytes_written)
            } else {
                Err("Failed to write process memory".to_string())
            }
        }
    }
}
