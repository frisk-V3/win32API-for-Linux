#include <sys/stat.h>

uint32_t GetFileAttributesW(const std::wstring& path) {
    std::string utf8(path.begin(), path.end());

    struct stat st;
    if (stat(utf8.c_str(), &st) != 0) {
        return (uint32_t)-1; // INVALID_FILE_ATTRIBUTES
    }

    uint32_t attr = 0;

    if (S_ISDIR(st.st_mode)) {
        attr |= 0x10; // FILE_ATTRIBUTE_DIRECTORY
    } else {
        attr |= 0x80; // FILE_ATTRIBUTE_NORMAL
    }

    if (!(st.st_mode & S_IWUSR)) {
        attr |= 0x1; // FILE_ATTRIBUTE_READONLY
    }

    return attr;
}
