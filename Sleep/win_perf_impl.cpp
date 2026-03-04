#include <time.h>

bool QueryPerformanceCounter(uint64_t* counter) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    *counter = ts.tv_sec * 1000000000ULL + ts.tv_nsec; // ナノ秒
    return true;
}

bool QueryPerformanceFrequency(uint64_t* freq) {
    *freq = 1000000000ULL; // CLOCK_MONOTONIC_RAW はナノ秒精度
    return true;
}
