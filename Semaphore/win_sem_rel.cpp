bool ReleaseSemaphore(SEM_HANDLE h, int releaseCount) {
    for (int i = 0; i < releaseCount; i++) {
        sem_post(&h->sem);
    }
    return true;
}
