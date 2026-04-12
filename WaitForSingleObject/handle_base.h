#pragma once
#include <windows.h>

enum class HandleKind {
    Unknown = 0,
    Process,
    Thread,
    Event,
    Mutex,
    Semaphore,
    File,    // 例：待機可能だが処理が異なるもの
    Socket   // 例：待機不可なもの
};

struct HandleEntry {
    HandleKind kind;
    void* object; // 実際のHANDLEを保持
};

// 待機可能なオブジェクトかどうかを判定する補助関数
inline bool IsWaitableKind(HandleKind kind) {
    switch (kind) {
        case HandleKind::Process:
        case HandleKind::Thread:
        case HandleKind::Event:
        case HandleKind::Mutex:
        case HandleKind::Semaphore:
            return true;
        default:
            return false;
    }
}
