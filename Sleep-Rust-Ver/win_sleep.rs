// 標準の sleep をラップしつつ、精度を意識する
pub fn sleep(ms: u64) {
    if ms == 0 { return; }
    
    // Windowsにおいて 1ms 単位の精度を要求する場合、
    // 本来は timeBeginPeriod(1) 等を呼ぶ必要があるが、
    // Rustの標準ライブラリはある程度最適化されている。
    thread::sleep(Duration::from_millis(ms));
}
