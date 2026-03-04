#include <codecvt>
#include <locale>

std::string utf16_to_utf8(const std::wstring& w) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.to_bytes(w);
}

std::wstring utf8_to_utf16(const std::string& s) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.from_bytes(s);
}
