#include <windows.h>
#include <iostream>
#include <memory>

// 1. RAIIによる自動解放（スマートポインタの活用）
struct VirtualFreeDeleter {
    void operator()(LPVOID p) const {
        if (p) {
            // MEM_RELEASE の場合、サイズは 0 である必要があります
            VirtualFree(p, 0, MEM_RELEASE);
        }
    }
};
using VirtualPtr = std::unique_ptr<void, VirtualFreeDeleter>;

void Example() {
    // 2. システムのページサイズを考慮する
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    size_t pageSize = si.dwPageSize;

    // 例: 1024バイト必要でも、実際は最小単位（通常4KB）で確保される
    size_t allocSize = (1024 + pageSize - 1) & ~(pageSize - 1);

    // 3. 安全なメモリ確保
    VirtualPtr pAddr(VirtualAlloc(nullptr, allocSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));

    if (!pAddr) {
        // エラー処理（GetLastError()で詳細取得可能）
        return;
    }

    // 書き込み処理...
    // pAddr.get() で生のポインタにアクセス
    auto data = static_cast<uint8_t*>(pAddr.get());
    data[0] = 0xFF;

    // スコープを抜ける際に自動的に VirtualFree されるため、リークの心配がない
}
