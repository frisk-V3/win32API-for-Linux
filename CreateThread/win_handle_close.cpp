bool CloseHandle(THREAD_HANDLE h) {
    if (!h) return false;
    delete h;
    return true;
}
