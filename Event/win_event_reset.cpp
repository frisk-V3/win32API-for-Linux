bool ResetEvent(EVENT_HANDLE h) {
    pthread_mutex_lock(&h->mutex);
    h->signaled = false;
    pthread_mutex_unlock(&h->mutex);
    return true;
}
