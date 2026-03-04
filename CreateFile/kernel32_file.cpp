#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <sys/stat.h>

struct HANDLE__ {
    int fd;
};
using HANDLE = HANDLE__*;

HANDLE CreateFileW(
    const std::wstring& path,
    FileAccess access,
    FileShare share,                 // Linux では無視
    CreationDisposition disp
) {
    // UTF-16 → UTF-8
    std::string utf8(path.begin(), path.end());

    int flags = to_posix_flags(access, disp);

    int fd = open(utf8.c_str(), flags, 0644);
    if (fd < 0) {
        return nullptr; // GetLastError() は errno を返すように別途実装
    }

    HANDLE h = new HANDLE__();
    h->fd = fd;
    return h;
}

bool ReadFile(HANDLE h, void* buffer, size_t size, size_t* bytesRead) {
    ssize_t r = read(h->fd, buffer, size);
    if (r < 0) return false;
    if (bytesRead) *bytesRead = r;
    return true;
}

bool WriteFile(HANDLE h, const void* buffer, size_t size, size_t* bytesWritten) {
    ssize_t w = write(h->fd, buffer, size);
    if (w < 0) return false;
    if (bytesWritten) *bytesWritten = w;
    return true;
}

bool CloseHandle(HANDLE h) {
    if (!h) return false;
    close(h->fd);
    delete h;
    return true;
}
