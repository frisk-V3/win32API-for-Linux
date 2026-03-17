#include <windows.h>

// デバッグ中のプロセスが OutputDebugString を呼んだ時にその内容を取得
extern "C" bool GetDebugString(HANDLE hProcess, const DEBUG_EVENT* pEvent, char* out_buffer, int max_len) {
    if (pEvent->dwDebugEventCode != OUTPUT_DEBUG_STRING_EVENT) return false;

    const OUTPUT_DEBUG_STRING_INFO& info = pEvent->u.DebugString;
    SIZE_T bytesRead = 0;
    
    // ターゲットプロセスのメモリから文字列をコピーしてくる
    return ReadProcessMemory(
        hProcess, 
        info.lpDebugStringData, 
        out_buffer, 
        min((int)info.nDebugStringLength, max_len - 1), 
        &bytesRead
    );
}

// 例外コードが「ブレークポイント（INT 3）」かどうかを判定
extern "C" bool IsBreakpointEvent(const DEBUG_EVENT* pEvent) {
    if (pEvent->dwDebugEventCode == EXCEPTION_DEBUG_EVENT) {
        return pEvent->u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_BREAKPOINT;
    }
    return false;
}
