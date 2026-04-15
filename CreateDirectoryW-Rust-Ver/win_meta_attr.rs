use std::fs;
use std::os::windows::fs::MetadataExt; // Windows固有の拡張を利用

pub fn get_file_attributes(path: &str) -> Option<u32> {
    // metadata() は内部的に GetFileInformationByHandle 等を呼んでいるため、
    // そこから生の dwFileAttributes を取り出すのが最速かつ最も正確。
    let meta = fs::metadata(path).ok()?;
    
    // Windows固有の属性値 (u32) をそのまま返す
    Some(meta.file_attributes())
}
