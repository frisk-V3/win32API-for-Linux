use std::time::Instant;

pub fn query_performance_counter() -> u128 {
    Instant::now().elapsed().as_nanos()
}

pub fn query_performance_frequency() -> u128 {
    1_000_000_000 // 1秒 = 10^9 ナノ秒
}
