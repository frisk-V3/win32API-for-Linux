// ページ単位のメモリ確保例
LPVOID pAddr = VirtualAlloc(NULL, 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
if (pAddr) {
    // 書き込み処理...
    VirtualFree(pAddr, 0, MEM_RELEASE);
}
