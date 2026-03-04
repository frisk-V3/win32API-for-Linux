pub fn errno_to_winerror(e: i32) -> u32 {
    match e {
        libc::ENOENT => 2,
        libc::EACCES => 5,
        libc::EEXIST => 183,
        libc::ENOMEM => 8,
        libc::EINVAL => 87,
        _ => e as u32,
    }
}
