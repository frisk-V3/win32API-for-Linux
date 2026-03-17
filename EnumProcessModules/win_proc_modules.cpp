#include <windows.h>
#include <psapi.h>
#include <vector>

// モジュール情報を格納する構造体
struct ModuleInfo {
    void* base_address;
    unsigned int size;
    wchar_t name[MAX_PATH];
};

// プロセスが読み込んでいるすべてのDLLをリストアップする
extern "C" int GetModuleList(HANDLE hProcess, ModuleInfo* out_list, int max_count) {
    HMODULE hMods[1024];
    DWORD cbNeeded;

    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
        int count = cbNeeded / sizeof(HMODULE);
        if (count > max_count) count = max_count;

        for (int i = 0; i < count; i++) {
            MODULEINFO mi;
            if (GetModuleInformation(hProcess, hMods[i], &mi, sizeof(mi))) {
                out_list[i].base_address = mi.lpBaseOfDll;
                out_list[i].size = mi.SizeOfImage;
                GetModuleBaseNameW(hProcess, hMods[i], out_list[i].name, MAX_PATH);
            }
        }
        return count;
    }
    return -1;
}
