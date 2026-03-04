uint32_t WaitForSingleObject(MUTEX_HANDLE h, uint32_t ms) {
    if (ms == 0xFFFFFFFF) { // INFINITE
        pthread_mutex_lock(&h->mutex);
        return 0; // WAIT_OBJECT_0
    }
    return 0xFFFFFFFF; // タイムアウト未対応（必要なら pthread_mutex_timedlock）
}
