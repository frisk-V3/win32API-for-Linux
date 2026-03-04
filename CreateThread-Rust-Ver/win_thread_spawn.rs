pub fn create_thread<F>(f: F) -> ThreadHandle
where
    F: FnOnce() -> u32 + Send + 'static,
{
    let handle = thread::spawn(f);
    ThreadHandle { handle }
}
