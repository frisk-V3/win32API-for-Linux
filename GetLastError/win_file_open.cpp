int fd = open(path, flags, 0644);
if (fd < 0) {
    SetLastError(errno_to_winerror(errno));
    return nullptr;
}
