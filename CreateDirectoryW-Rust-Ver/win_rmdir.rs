pub fn remove_directory(path: &str) -> bool {
    fs::remove_dir(path).is_ok()
}
