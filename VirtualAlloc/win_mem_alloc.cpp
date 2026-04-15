#include <windows.h>
#include <iostream>
#include <memory>
#include <cstdint>

// 1. デリータの洗練：noexcept の付与と、型安全な unique_ptr
struct VirtualFreeDeleter {
    void operator()(void* p) const noexcept {
        if (p) {
            // VirtualFree が失敗することは稀だが、デバッグ時は成否を確認すべき
            if (!VirtualFree(p, 0, MEM_RELEASE)) {
                // 必要に応じてログ出力など
            }
        }
    }
};

// バイト単位で操作しやすいよう、デフォルトを uint8_t に設定
using VirtualMemoryPtr = std::unique_ptr<uint8_t[], VirtualFreeDeleter>;

// アライメント計算をユーティリティ化
inline size_t align_to_page(size_t size, size_t pageSize) noexcept {
    return (size + pageSize - 1) & ~(pageSize - 1);
}

void SecureMemoryExample() {
    // システム情報の取得
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    const size_t pageSize = si.dwPageSize;

    // 2. 必要なサイズをページ単位に切り上げ
    const size_t requestedSize = 1024;
    const size_t allocSize = align_to_page(requestedSize, pageSize);

    // 3. メモリの確保 (COMMIT と RESERVE を同時に行う)
    VirtualMemoryPtr pData(static_cast<uint8_t*>(
        VirtualAlloc(nullptr, allocSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)
    ));

    if (!pData) {
        // DWORD error = GetLastError();
        return;
    }

    // --- データの書き込み ---
    pData[0] = 0xDE;
    pData[1] = 0xAD;
    pData[2] = 0xBE;
    pData[3] = 0xEF;

    // 4. 「本気」の仕上げ：書き込みが終わったら保護属性を変更する
    // これにより、不慮の書き込み（バグや攻撃）によるデータ改ざんを防止
    DWORD oldProtect;
    if (VirtualProtect(pData.get(), allocSize, PAGE_READONLY, &oldProtect)) {
        // これ以降、pData[0] = 0x00; などを行うとアクセス違反で即座にクラッシュする（安全）
    }

    // スコープ終了時に VirtualFree が自動的に呼ばれる
}
