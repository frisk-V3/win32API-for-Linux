use std::os::raw::c_void;

// これまでの GetProcessList を利用して特定の名前のPIDを探す
pub fn find_process_by_name(target_name: &str) -> Option<u32> {
    let processes = super::win_proc_list::enumerate_processes(); // 前に作った関数
    processes.into_iter()
        .find(|p| p.name.to_lowercase() == target_name.to_lowercase())
        .map(|p| p.pid)
}
