#include <windows.h>

// デバッガとしてプロセスにアタッチする
extern "C" bool AttachDebugger(DWORD dwProcessId) {
    return DebugActiveProcess(dwProcessId);
}

// アタッチを解除する
extern "C" bool DetachDebugger(DWORD dwProcessId) {
    return DebugActiveProcessStop(dwProcessId);
}

// プロセス内で起きたイベント（ブレークポイント、例外など）を1つ取得する
extern "C" bool WaitForDebugEventSafe(LPDEBUG_EVENT lpDebugEvent, DWORD dwMilliseconds) {
    return WaitForDebugEvent(lpDebugEvent, dwMilliseconds);
}

// デバッグイベントの処理を終えて実行を再開させる
extern "C" bool ContinueDebug(DWORD dwProcessId, DWORD dwThreadId, DWORD dwContinueStatus) {
    return ContinueDebugEvent(dwProcessId, dwThreadId, dwContinueStatus);
}
