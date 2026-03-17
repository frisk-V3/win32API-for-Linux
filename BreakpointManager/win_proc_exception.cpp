#include <windows.h>

// 例外の種類（コード）をわかりやすい文字列に変換する
extern "C" const char* GetExceptionCodeString(DWORD code) {
    switch (code) {
        case EXCEPTION_ACCESS_VIOLATION: return "Access Violation (0xc0000005)";
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: return "Array Bounds Exceeded";
        case EXCEPTION_BREAKPOINT: return "Breakpoint Reached";
        case EXCEPTION_DATATYPE_MISALIGNMENT: return "Datatype Misalignment";
        case EXCEPTION_FLT_DIVIDE_BY_ZERO: return "Floating-point Divide by Zero";
        case EXCEPTION_INT_DIVIDE_BY_ZERO: return "Integer Divide by Zero";
        case EXCEPTION_STACK_OVERFLOW: return "Stack Overflow";
        default: return "Unknown Exception";
    }
}

// 例外が発生したアドレスを取得する
extern "C" PVOID GetExceptionAddress(const DEBUG_EVENT* pEvent) {
    if (pEvent->dwDebugEventCode == EXCEPTION_DEBUG_EVENT) {
        return pEvent->u.Exception.ExceptionRecord.ExceptionAddress;
    }
    return NULL;
}
