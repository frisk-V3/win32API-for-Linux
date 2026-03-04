#include <chrono>
#include <thread>

void Sleep(uint32_t ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
