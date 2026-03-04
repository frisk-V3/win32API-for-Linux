FIND_HANDLE FindFirstFileW(const std::wstring& searchPath, WIN32_FIND_DATAW* data) {
    // パスを directory + pattern に分割
    size_t pos = searchPath.find_last_of(L"/\\");
    std::wstring directory = (pos == std::wstring::npos) ? L"." : searchPath.substr(0, pos);
    std::wstring pattern   = searchPath.substr(pos + 1);

    // UTF-16 → UTF-8
    std::string dir_utf8(directory.begin(), directory.end());

    DIR* dir = opendir(dir_utf8.c_str());
    if (!dir) return nullptr;

    FIND_HANDLE h = new FIND_HANDLE__();
    h->dir = dir;
    h->pattern = pattern;
    h->directory = directory;

    // 最初の一致を探す
    struct dirent* ent;
    while ((ent = readdir(dir)) != nullptr) {
        std::wstring name(ent->d_name, ent->d_name + strlen(ent->d_name));
        if (wildcard_match(pattern, name)) {
            data->cFileName = name;
            data->dwFileAttributes = (ent->d_type == DT_DIR) ? 0x10 : 0x80;
            data->nFileSize = 0; // stat() で取得可能
            return h;
        }
    }

    closedir(dir);
    delete h;
    return nullptr;
}
