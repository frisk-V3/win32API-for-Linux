struct EVENT_HANDLE__ {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    bool signaled;
    bool manualReset;
};
using EVENT_HANDLE = EVENT_HANDLE__*;
