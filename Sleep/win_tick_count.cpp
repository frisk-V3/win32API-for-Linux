#include <time.h>

uint32_t GetTickCount() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    uint64_t ms = ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000ULL;
    return (uint32_t)ms; // Win32 と同じくオーバーフローする
}
