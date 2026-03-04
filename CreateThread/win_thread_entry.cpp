struct ThreadStartInfo {
    LPTHREAD_START_ROUTINE startRoutine;
    void* parameter;
    THREAD_HANDLE handle;
};

void* thread_entry(void* arg) {
    ThreadStartInfo* info = (ThreadStartInfo*)arg;

    void* ret = info->startRoutine(info->parameter);

    info->handle->exitCode = ret;
    return ret;
}
