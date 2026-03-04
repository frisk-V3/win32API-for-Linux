use std::fs::{OpenOptions, File};
use std::io::{Read, Write, Result};

#[derive(Clone, Copy)]
pub enum FileAccess {
    Read,
    Write,
    ReadWrite,
}

#[derive(Clone, Copy)]
pub enum CreationDisposition {
    CreateNew,
    CreateAlways,
    OpenExisting,
    OpenAlways,
    TruncateExisting,
}

pub struct Handle {
    file: File,
}

pub fn create_file(
    path: &str,
    access: FileAccess,
    disp: CreationDisposition,
) -> Result<Handle> {
    let mut opt = OpenOptions::new();

    match access {
        FileAccess::Read => opt.read(true),
        FileAccess::Write => opt.write(true),
        FileAccess::ReadWrite => opt.read(true).write(true),
    };

    match disp {
        CreationDisposition::CreateNew => opt.create_new(true),
        CreationDisposition::CreateAlways => opt.create(true).truncate(true),
        CreationDisposition::OpenExisting => {},
        CreationDisposition::OpenAlways => opt.create(true),
        CreationDisposition::TruncateExisting => opt.truncate(true),
    };

    let file = opt.open(path)?;
    Ok(Handle { file })
}

impl Handle {
    pub fn read(&mut self, buf: &mut [u8]) -> Result<usize> {
        self.file.read(buf)
    }

    pub fn write(&mut self, buf: &[u8]) -> Result<usize> {
        self.file.write(buf)
    }
}
