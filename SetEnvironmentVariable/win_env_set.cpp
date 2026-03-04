#include <cstdlib>
#include <string>
#include <cwchar>

// 事前に：
// - utf16_to_utf8
// - SetLastError
// - ERROR_INVALID_PARAMETER
// が定義されている前提

constexpr uint32_t ERROR_INVALID_PARAMETER = 87;

BOOL SetEnvironmentVariableW(
    LPCWSTR lpName,
    LPCWSTR lpValue
) {
    // 名前チェック
    if (!lpName || lpName[0] == L'\0') {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    // 名前に '=' が含まれていたらエラー
    if (std::wcschr(lpName, L'=')) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    // UTF-16 → UTF-8
    std::wstring wname(lpName);
    std::string utf8Name = utf16_to_utf8(wname);

    // 削除（lpValue == NULL）
    if (!lpValue) {
        if (unsetenv(utf8Name.c_str()) != 0) {
            // unsetenv は存在しない変数でも成功扱いだが、
            // 失敗した場合は errno を Win32 エラーに変換する必要がある
            SetLastError(errno_to_winerror(errno));
            return FALSE;
        }
        return TRUE;
    }

    // 設定（lpValue != NULL）
    std::wstring wvalue(lpValue);
    std::string utf8Value = utf16_to_utf8(wvalue);

    if (setenv(utf8Name.c_str(), utf8Value.c_str(), 1) != 0) {
        SetLastError(errno_to_winerror(errno));
        return FALSE;
    }

    return TRUE;
}
