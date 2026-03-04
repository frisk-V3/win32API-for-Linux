MUTEX_HANDLE CreateMutexW(bool initialOwner) {
    MUTEX_HANDLE h = new MUTEX_HANDLE__();
    pthread_mutex_init(&h->mutex, nullptr);

    if (initialOwner) {
        pthread_mutex_lock(&h->mutex);
    }

    return h;
}
