SEM_HANDLE CreateSemaphoreW(int initialCount, int maxCount) {
    SEM_HANDLE h = new SEM_HANDLE__();
    sem_init(&h->sem, 0, initialCount);
    return h;
}
