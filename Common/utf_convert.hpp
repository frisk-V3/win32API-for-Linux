// utf_convert.hpp

#ifndef UTF_CONVERT_HPP
#define UTF_CONVERT_HPP

#include <string>
#include <windows.h>

// Function to convert UTF-8 to UTF-16
std::wstring utf8_to_utf16(const std::string& utf8) {
    int wideSize = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
    std::wstring utf16(wideSize, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &utf16[0], wideSize);
    return utf16;
}

// Function to convert UTF-16 to UTF-8
std::string utf16_to_utf8(const std::wstring& utf16) {
    int utf8Size = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, NULL, 0, NULL, NULL);
    std::string utf8(utf8Size, '\0');
    WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, &utf8[0], utf8Size, NULL, NULL);
    return utf8;
}

#endif // UTF_CONVERT_HPP