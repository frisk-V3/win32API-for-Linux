#include <windows.h>

// スレッドのCPUレジスタ（CONTEXT）を取得する
extern "C" bool GetThreadContextSafe(HANDLE hThread, LPCONTEXT lpContext) {
    // CONTEXT構造体はアライメントが重要なので、呼び出し側で適切に確保されている前提
    lpContext->ContextFlags = CONTEXT_ALL; 
    return GetThreadContext(hThread, lpContext);
}

// スレッドのCPUレジスタを書き換える（次の命令を飛ばす時などに使用）
extern "C" bool SetThreadContextSafe(HANDLE hThread, const CONTEXT* lpContext) {
    return SetThreadContext(hThread, lpContext);
}

// スレッドを一時停止/再開させる（デバッガが特定の糸だけ止めたい時用）
extern "C" DWORD SuspendThreadSafe(HANDLE hThread) {
    return SuspendThread(hThread);
}

extern "C" DWORD ResumeThreadSafe(HANDLE hThread) {
    return ResumeThread(hThread);
}
