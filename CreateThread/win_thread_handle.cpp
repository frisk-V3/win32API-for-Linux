struct THREAD_HANDLE__ {
    pthread_t thread;
    void* exitCode;
};
using THREAD_HANDLE = THREAD_HANDLE__*;
