THREAD_HANDLE CreateThread(
    void* lpThreadAttributes,
    size_t dwStackSize,
    LPTHREAD_START_ROUTINE lpStartAddress,
    void* lpParameter,
    uint32_t dwCreationFlags,
    uint32_t* lpThreadId
) {
    THREAD_HANDLE h = new THREAD_HANDLE__();
    h->exitCode = nullptr;

    ThreadStartInfo* info = new ThreadStartInfo();
    info->startRoutine = lpStartAddress;
    info->parameter = lpParameter;
    info->handle = h;

    pthread_t thread;
    int r = pthread_create(&thread, nullptr, thread_entry, info);
    if (r != 0) {
        delete info;
        delete h;
        return nullptr;
    }

    h->thread = thread;

    if (lpThreadId) {
        *lpThreadId = (uint32_t)thread; // 疑似的な ID
    }

    return h;
}
