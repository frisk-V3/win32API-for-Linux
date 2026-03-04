#include <cstdlib>   // getenv
#include <cwchar>    // wcslen, wcsncpy

// 事前に：
// - utf16_to_utf8
// - utf8_to_utf16
// - SetLastError / GetLastError
// - ERROR_ENVVAR_NOT_FOUND
// が定義されている前提

DWORD GetEnvironmentVariableW(
    LPCWSTR lpName,
    LPWSTR  lpBuffer,
    DWORD   nSize
) {
    if (!lpName) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;
    }

    // 名前を UTF-8 に変換
    std::wstring name(lpName);
    std::string utf8Name = utf16_to_utf8(name);

    const char* val = std::getenv(utf8Name.c_str());
    if (!val) {
        // 変数が存在しない
        SetLastError(ERROR_ENVVAR_NOT_FOUND);
        return 0;
    }

    // 値を UTF-16 に変換
    std::string utf8Val(val);
    std::wstring wval = utf8_to_utf16(utf8Val);

    DWORD needed = static_cast<DWORD>(wval.size() + 1); // 終端込み

    // nSize == 0 の場合：バッファには書かず、必要サイズだけ返す
    if (nSize == 0) {
        return needed;
    }

    // バッファ不足
    if (nSize < needed) {
        // バッファには何も書かない（Win32 と同じ）
        return needed;
    }

    // バッファにコピー（終端含む）
    std::wcsncpy(lpBuffer, wval.c_str(), nSize);
    lpBuffer[needed - 1] = L'\0';

    // 成功時は「終端を含まない文字数」を返す
    return needed - 1;
}
