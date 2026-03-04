pub fn get_last_error() -> u32 {
    LAST_ERROR.with(|e| e.get())
}
