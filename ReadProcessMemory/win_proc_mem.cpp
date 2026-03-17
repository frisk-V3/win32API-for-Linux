#include <windows.h>
#include <vector>

// プロセスのメモリを安全に読み取る
extern "C" bool ReadProcessMemorySafe(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) {
    return ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}

// プロセスのメモリを書き換える（ブレークポイント設置などに使用）
extern "C" bool WriteProcessMemorySafe(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten) {
    // 書き込み権限がない場合に備え、一時的に保護属性を変更する処理を入れるのが「VS」流
    DWORD oldProtect;
    if (VirtualProtectEx(hProcess, lpBaseAddress, nSize, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        bool result = WriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
        VirtualProtectEx(hProcess, lpBaseAddress, nSize, oldProtect, &oldProtect);
        return result;
    }
    return false;
}

// 特定のアドレスのメモリ属性（読み取り専用か等）を調べる
extern "C" bool QueryMemoryRegion(HANDLE hProcess, LPCVOID lpAddress, MEMORY_BASIC_INFORMATION* lpBuffer) {
    return VirtualQueryEx(hProcess, lpAddress, lpBuffer, sizeof(MEMORY_BASIC_INFORMATION)) != 0;
}
