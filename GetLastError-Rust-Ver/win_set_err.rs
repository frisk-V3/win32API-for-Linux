pub fn set_last_error(err: u32) {
    LAST_ERROR.with(|e| e.set(err));
}
