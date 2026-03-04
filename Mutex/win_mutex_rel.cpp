bool ReleaseMutex(MUTEX_HANDLE h) {
    return pthread_mutex_unlock(&h->mutex) == 0;
}
