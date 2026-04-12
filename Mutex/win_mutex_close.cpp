bool CloseHandle(MUTEX_HANDLE h) {
    if (h == nullptr) return false;

    int result = pthread_mutex_destroy(&h->mutex);
    
    delete h; 
    return (result == 0);
}
