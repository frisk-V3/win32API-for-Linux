#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>

// 改善版 FindFirstFileW
FIND_HANDLE FindFirstFileW(const std::wstring& searchPath, WIN32_FIND_DATAW* data) {
    if (!data) return nullptr;

    // 1. パスを directory と pattern に分離
    size_t pos = searchPath.find_last_of(L"/\\");
    std::wstring directory = (pos == std::wstring::npos) ? L"." : searchPath.substr(0, pos);
    std::wstring pattern   = (pos == std::wstring::npos) ? searchPath : searchPath.substr(pos + 1);

    // 2. ディレクトリを開く (UTF-16 -> UTF-8 変換は環境に依存するため簡易実装)
    std::string dir_utf8(directory.begin(), directory.end());
    DIR* dir = opendir(dir_utf8.empty() ? "." : dir_utf8.c_str());
    if (!dir) return nullptr;

    // 3. 管理オブジェクトの生成
    FIND_HANDLE h = new FIND_HANDLE__();
    h->dir = dir;
    h->pattern = pattern;
    h->directory = directory;

    // 4. 最初の一致が見つかるまでループ
    struct dirent* ent;
    while ((ent = readdir(dir)) != nullptr) {
        // UTF-8 -> UTF-16 (簡易)
        std::string d_name_utf8(ent->d_name);
        std::wstring name(d_name_utf8.begin(), d_name_utf8.end());

        // ワイルドカード比較 (例: *.* や *.txt)
        if (wildcard_match(pattern, name)) {
            // 5. 詳細情報の取得 (stat を使用)
            std::wstring fullPath = directory + L"/" + name;
            std::string fullPath_utf8(fullPath.begin(), fullPath.end());
            
            struct stat st;
            if (stat(fullPath_utf8.c_str(), &st) == 0) {
                // ファイル名コピー
                wcsncpy(data->cFileName, name.c_str(), MAX_PATH);
                
                // 属性の設定
                data->dwFileAttributes = S_ISDIR(st.st_mode) ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL;
                
                // サイズの設定 (低位/高位 32bit)
                data->nFileSizeLow = static_cast<DWORD>(st.st_size & 0xFFFFFFFF);
                data->nFileSizeHigh = static_cast<DWORD>((st.st_size >> 32) & 0xFFFFFFFF);
                
                // タイムスタンプ（必要であれば st.st_mtime から変換）
                return h;
            }
        }
    }

    // 一致が見つからなかった場合、リソースを解放して終了
    closedir(dir);
    delete h;
    return nullptr;
}
