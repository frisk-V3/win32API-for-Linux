bool CloseHandle(MUTEX_HANDLE h) {
    pthread_mutex_destroy(&h->mutex);
    delete h;
    return true;
}
