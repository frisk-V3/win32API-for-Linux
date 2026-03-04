#include <unistd.h>

bool RemoveDirectoryW(const std::wstring& path) {
    std::string utf8(path.begin(), path.end());

    int r = rmdir(utf8.c_str());
    if (r == 0) return true;

    return false;
}
