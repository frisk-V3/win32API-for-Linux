use std::process::{Command, Child};

pub struct ProcessInformation {
    pub child: Child,
}

pub fn create_process(app: &str, args: &[&str]) -> Option<ProcessInformation> {
    let child = Command::new(app)
        .args(args)
        .spawn()
        .ok()?;

    Some(ProcessInformation { child })
}
