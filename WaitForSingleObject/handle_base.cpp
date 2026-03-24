#pragma once
#include <cstdint>

enum class HandleKind {
    Process,
    Thread,
    Event,
    Mutex,
    Semaphore
};

struct HandleEntry {
    HandleKind kind;
    void* object;
};
