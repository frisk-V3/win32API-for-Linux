#pragma once
#include <mutex>
#include <condition_variable>

class WinEvent {
public:
    WinEvent(bool manualReset, bool initialState)
        : manualReset(manualReset), signaled(initialState) {}

    void set() {
        std::unique_lock<std::mutex> lock(mtx);
        signaled = true;

        if (manualReset) {
            cv.notify_all();
        } else {
            cv.notify_one();
        }
    }

    void reset() {
        std::unique_lock<std::mutex> lock(mtx);
        signaled = false;
    }

    bool wait(uint32_t timeout_ms);

private:
    bool manualReset;
    bool signaled;

    std::mutex mtx;
    std::condition_variable cv;
};
