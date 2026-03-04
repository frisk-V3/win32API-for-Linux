impl ThreadHandle {
    pub fn wait(self) -> u32 {
        self.handle.join().unwrap_or(0)
    }
}
