#include <string>
#include <locale>
#include <codecvt>

/**
 * UTF-16 (wstring) -> UTF-8 (string)
 */
std::string utf16_to_utf8(const std::wstring& w) {
    if (w.empty()) return {};

    // 非推奨(deprecated)の警告を抑制しつつ、標準ライブラリで完結
#if defined(_MSC_VER)
    #pragma warning(suppress : 4996)
#endif
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.to_bytes(w);
}

/**
 * UTF-8 (string) -> UTF-16 (wstring)
 */
std::wstring utf8_to_utf16(const std::string& s) {
    if (s.empty()) return {};

#if defined(_MSC_VER)
    #pragma warning(suppress : 4996)
#endif
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.from_bytes(s);
}
