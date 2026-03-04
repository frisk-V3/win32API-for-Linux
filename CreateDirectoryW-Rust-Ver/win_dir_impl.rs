use std::fs;

pub fn create_directory(path: &str) -> bool {
    fs::create_dir(path).is_ok()
}
