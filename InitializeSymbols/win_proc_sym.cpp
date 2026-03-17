#include <windows.h>
#include <dbghelp.h>
#include <iostream>

#pragma comment(lib, "dbghelp.lib")

// プロセスのシンボル初期化（PDBファイルの読み込み準備）
extern "C" bool InitializeSymbols(HANDLE hProcess) {
    // ユーザー検索パス（カレントディレクトリや環境変数）を考慮して初期化
    return SymInitialize(hProcess, NULL, TRUE);
}

// アドレスから関数名を取得する
extern "C" bool GetFunctionNameFromAddr(HANDLE hProcess, DWORD64 address, char* out_name, int max_len) {
    char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
    PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;

    pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    pSymbol->MaxNameLen = MAX_SYM_NAME;

    DWORD64 displacement = 0;
    if (SymFromAddr(hProcess, address, &displacement, pSymbol)) {
        strncpy_s(out_name, max_len, pSymbol->Name, _TRUNCATE);
        return true;
    }
    return false;
}

// シンボル情報のクリーンアップ
extern "C" void CleanupSymbols(HANDLE hProcess) {
    SymCleanup(hProcess);
}
