use std::thread;
use std::time::Duration;

pub fn sleep(ms: u64) {
    thread::sleep(Duration::from_millis(ms));
}
