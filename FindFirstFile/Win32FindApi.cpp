bool FindClose(FIND_HANDLE h) {
    if (!h) return false;
    closedir(h->dir);
    delete h;
    return true;
}
