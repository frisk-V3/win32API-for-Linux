struct MUTEX_HANDLE__ {
    pthread_mutex_t mutex;
};
using MUTEX_HANDLE = MUTEX_HANDLE__*;
