#include <windows.h>
#include <tlhelp32.h>

// スレッドIDをリストアップする
extern "C" int GetThreadList(DWORD dwProcessId, DWORD* out_tid_list, int max_count) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return -1;

    THREADENTRY32 te32;
    te32.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hSnapshot, &te32)) {
        CloseHandle(hSnapshot);
        return -1;
    }

    int count = 0;
    do {
        // 指定したプロセスIDに属するスレッドだけを抽出
        if (te32.th32OwnerProcessID == dwProcessId) {
            if (count < max_count) {
                out_tid_list[count] = te32.th32ThreadID;
                count++;
            }
        }
    } while (Thread32Next(hSnapshot, &te32));

    CloseHandle(hSnapshot);
    return count;
}
