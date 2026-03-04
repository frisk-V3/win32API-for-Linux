bool FindNextFileW(FIND_HANDLE h, WIN32_FIND_DATAW* data) {
    struct dirent* ent;

    while ((ent = readdir(h->dir)) != nullptr) {
        std::wstring name(ent->d_name, ent->d_name + strlen(ent->d_name));
        if (wildcard_match(h->pattern, name)) {
            data->cFileName = name;
            data->dwFileAttributes = (ent->d_type == DT_DIR) ? 0x10 : 0x80;
            data->nFileSize = 0;
            return true;
        }
    }

    return false;
}
