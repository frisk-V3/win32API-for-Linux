impl ProcessInformation {
    pub fn wait(&mut self) -> bool {
        self.child.wait().is_ok()
    }
}
