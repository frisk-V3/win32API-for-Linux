use std::ptr::NonNull;
use windows::Win32::System::Memory::{
    VirtualAlloc, VirtualFree, MEM_COMMIT, MEM_RESERVE, PAGE_READWRITE, VIRTUAL_ALLOCATION_TYPE, PAGE_PROTECTION_FLAGS, MEM_RELEASE
};

pub struct VirtualBuffer {
    ptr: NonNull<std::ffi::c_void>,
    size: usize,
}

impl VirtualBuffer {
    pub fn new(size: usize) -> Result<Self, String> {
        unsafe {
            let addr = VirtualAlloc(
                None,
                size,
                MEM_COMMIT | MEM_RESERVE,
                PAGE_READWRITE
            );

            if addr.is_null() {
                return Err("VirtualAlloc failed".to_string());
            }

            Ok(Self {
                ptr: NonNull::new_unchecked(addr),
                size,
            })
        }
    }

    // スライスとして安全に露出させる
    pub fn as_slice_mut(&mut self) -> &mut [u8] {
        unsafe { std::slice::from_raw_parts_mut(self.ptr.as_ptr() as *mut u8, self.size) }
    }
}

impl Drop for VirtualBuffer {
    fn drop(&mut self) {
        unsafe {
            // 第2引数は MEM_RELEASE の場合 0 でなければならない（Win32のルール）
            let _ = VirtualFree(self.ptr.as_ptr(), 0, MEM_RELEASE);
            println!("Memory released safely!");
        }
    }
}
