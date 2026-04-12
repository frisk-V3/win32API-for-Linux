#include <windows.h>
#include "handle_base.h"
#include "wait_result.h"

// 外部で定義されているハンドル解決関数
extern HandleEntry* ResolveHandle(void* h);

/**
 * 自前ハンドルを解決し、Windows標準の待機処理を行う
 */
DWORD WinWaitForSingleObject(void* h, DWORD timeout)
{
    // 1. ハンドルの解決
    const auto entry = ResolveHandle(h);

    // 2. バリデーション（ガード句）
    if (!entry) {
        SetLastError(ERROR_INVALID_HANDLE);
        return WAIT_FAILED;
    }

    if (!IsWaitableKind(entry->kind)) {
        // 待機不可能なオブジェクト（FileやSocketなど）が渡された場合
        SetLastError(ERROR_NOT_SUPPORTED);
        return WAIT_FAILED;
    }

    // 3. 実行（共通化された呼び出し）
    // void* から HANDLE への変換は static_cast を使用
    HANDLE realHandle = static_cast<HANDLE>(entry->object);
    return WaitForSingleObject(realHandle, timeout);
}
