int to_posix_flags(FileAccess access, CreationDisposition disp) {
    int flags = 0;

    // アクセス権
    if (access == FileAccess::Read) flags |= O_RDONLY;
    else if (access == FileAccess::Write) flags |= O_WRONLY;
    else flags |= O_RDWR;

    // 作成モード
    switch (disp) {
        case CreationDisposition::CreateNew:
            flags |= O_CREAT | O_EXCL;
            break;
        case CreationDisposition::CreateAlways:
            flags |= O_CREAT | O_TRUNC;
            break;
        case CreationDisposition::OpenExisting:
            break;
        case CreationDisposition::OpenAlways:
            flags |= O_CREAT;
            break;
        case CreationDisposition::TruncateExisting:
            flags |= O_TRUNC;
            break;
    }

    return flags;
}
