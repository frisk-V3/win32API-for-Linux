pub fn find_first_file(path: &str) -> Option<(FindHandle, String)> {
    let (dir, pattern) = split_path(path);
    let rd = std::fs::read_dir(&dir).ok()?;

    let mut handle = FindHandle { dir: rd, pattern };

    for entry in handle.dir.by_ref() {
        if let Ok(e) = entry {
            let name = e.file_name().to_string_lossy().to_string();
            if wildcard_match(&handle.pattern, &name) {
                return Some((handle, name));
            }
        }
    }

    None
}
