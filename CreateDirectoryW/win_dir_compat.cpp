#include <sys/stat.h>
#include <errno.h>
#include <string>

bool CreateDirectoryW(const std::wstring& path) {
    std::string utf8(path.begin(), path.end());

    int r = mkdir(utf8.c_str(), 0755);
    if (r == 0) return true;

    // Win32 の GetLastError に相当する errno を保存する仕組みは別途作る
    return false;
}
