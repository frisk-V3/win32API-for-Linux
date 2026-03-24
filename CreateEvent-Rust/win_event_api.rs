use std::sync::Arc;
use crate::win_event::WinEvent;
use crate::handle::{Handle, HandleObject};

extern "Rust" {
    fn allocate_handle(obj: HandleObject) -> Handle;
    fn resolve_handle(h: Handle) -> *const HandleObject;
}

pub fn create_event(manual_reset: bool, initial_state: bool) -> Handle {
    let ev = Arc::new(WinEvent::new(manual_reset, initial_state));
    unsafe { allocate_handle(HandleObject::Event(ev)) }
}

pub fn set_event(h: Handle) -> bool {
    unsafe {
        match &*resolve_handle(h) {
            HandleObject::Event(ev) => {
                ev.set();
                true
            }
            _ => false,
        }
    }
}

pub fn reset_event(h: Handle) -> bool {
    unsafe {
        match &*resolve_handle(h) {
            HandleObject::Event(ev) => {
                ev.reset();
                true
            }
            _ => false,
        }
    }
}
