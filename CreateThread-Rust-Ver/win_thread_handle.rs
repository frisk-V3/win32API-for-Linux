use std::thread::{self, JoinHandle};

pub struct ThreadHandle {
    handle: JoinHandle<u32>,
}
