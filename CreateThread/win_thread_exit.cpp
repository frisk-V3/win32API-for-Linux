bool GetExitCodeThread(THREAD_HANDLE h, uint32_t* exitCode) {
    if (!h || !exitCode) return false;
    *exitCode = (uint32_t)(uintptr_t)h->exitCode;
    return true;
}
