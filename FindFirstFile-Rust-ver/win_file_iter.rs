pub fn find_next_file(handle: &mut FindHandle) -> Option<String> {
    for entry in handle.dir.by_ref() {
        if let Ok(e) = entry {
            let name = e.file_name().to_string_lossy().to_string();
            if wildcard_match(&handle.pattern, &name) {
                return Some(name);
            }
        }
    }
    None
}
