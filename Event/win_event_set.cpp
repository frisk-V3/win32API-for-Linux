bool SetEvent(EVENT_HANDLE h) {
    pthread_mutex_lock(&h->mutex);
    h->signaled = true;
    if (h->manualReset)
        pthread_cond_broadcast(&h->cond);
    else
        pthread_cond_signal(&h->cond);
    pthread_mutex_unlock(&h->mutex);
    return true;
}
