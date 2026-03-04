EVENT_HANDLE CreateEventW(bool manualReset, bool initialState) {
    EVENT_HANDLE h = new EVENT_HANDLE__();
    pthread_mutex_init(&h->mutex, nullptr);
    pthread_cond_init(&h->cond, nullptr);
    h->signaled = initialState;
    h->manualReset = manualReset;
    return h;
}
