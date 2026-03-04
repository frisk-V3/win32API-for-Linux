uint32_t WaitForSingleObject(THREAD_HANDLE h, uint32_t milliseconds) {
    void* ret = nullptr;
    int r = pthread_join(h->thread, &ret);
    if (r != 0) return 0xFFFFFFFF; // WAIT_FAILED
    h->exitCode = ret;
    return 0; // WAIT_OBJECT_0
}
