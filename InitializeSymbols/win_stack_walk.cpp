#include <windows.h>
#include <dbghelp.h>
#include <vector>

// 現在のスレッドのスタックを1段階遡る
extern "C" bool WalkNextStackFrame(HANDLE hProcess, HANDLE hThread, STACKFRAME64* frame, CONTEXT* context) {
    // x64環境を想定したスタックウォーク
    return StackWalk64(
        IMAGE_FILE_MACHINE_AMD64,
        hProcess,
        hThread,
        frame,
        context,
        NULL,
        SymFunctionTableAccess64,
        SymGetModuleBase64,
        NULL
    );
}

// スタックフレームの初期化（これを呼んでからWalkNextStackFrameをループさせる）
extern "C" void InitStackFrame(STACKFRAME64* frame, const CONTEXT* context) {
    ZeroMemory(frame, sizeof(STACKFRAME64));
    frame->AddrPC.Offset = context->Rip;
    frame->AddrPC.Mode = AddrModeFlat;
    frame->AddrFrame.Offset = context->Rbp;
    frame->AddrFrame.Mode = AddrModeFlat;
    frame->AddrStack.Offset = context->Rsp;
    frame->AddrStack.Mode = AddrModeFlat;
}
