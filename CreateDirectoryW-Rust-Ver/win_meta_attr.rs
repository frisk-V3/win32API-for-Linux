use std::fs;

pub fn get_file_attributes(path: &str) -> Option<u32> {
    let meta = fs::metadata(path).ok()?;

    let mut attr = 0;

    if meta.is_dir() {
        attr |= 0x10; // DIRECTORY
    } else {
        attr |= 0x80; // NORMAL
    }

    if meta.permissions().readonly() {
        attr |= 0x1; // READONLY
    }

    Some(attr)
}
