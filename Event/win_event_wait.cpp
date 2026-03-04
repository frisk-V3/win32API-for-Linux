uint32_t WaitForSingleObject(EVENT_HANDLE h, uint32_t ms) {
    pthread_mutex_lock(&h->mutex);

    while (!h->signaled) {
        pthread_cond_wait(&h->cond, &h->mutex);
    }

    if (!h->manualReset) {
        h->signaled = false;
    }

    pthread_mutex_unlock(&h->mutex);
    return 0; // WAIT_OBJECT_0
}
