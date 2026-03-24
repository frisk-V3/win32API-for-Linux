use std::sync::Arc;

pub type Handle = u64;

pub enum HandleObject {
    Event(Arc<crate::win_event::WinEvent>),
    // 他：Process, Thread, etc
}

pub struct HandleEntry {
    pub obj: HandleObject,
}
