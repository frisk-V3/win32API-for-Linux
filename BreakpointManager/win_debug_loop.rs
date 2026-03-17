pub fn start_debug_loop(pid: u32) {
    let session = super::win_debug_core::DebugSession::attach(pid).unwrap();
    let mut bp_manager = BreakpointManager::new();

    println!("Debugger attached to PID: {}", pid);

    loop {
        if let Some(event) = session.wait_for_event(100) {
            // イベントの種類に応じて処理を分岐
            match event.event_code {
                1 => { // EXCEPTION_DEBUG_EVENT
                    println!("Exception caught!");
                    // ここでスタックトレースやレジスタを表示する
                },
                5 => { // EXIT_PROCESS_DEBUG_EVENT
                    println!("Process exited.");
                    break;
                },
                _ => {}
            }
            // 実行再開
            session.continue_execution(event.thread_id, 0x00010002); // DBG_CONTINUE
        }
    }
}
