use std::time::{SystemTime, UNIX_EPOCH};

pub fn get_tick_count() -> u32 {
    let now = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap();
    (now.as_millis() as u64 % u32::MAX as u64) as u32
}
