uint32_t WaitForSingleObject(SEM_HANDLE h, uint32_t ms) {
    sem_wait(&h->sem);
    return 0; // WAIT_OBJECT_0
}
