#include <windows.h>
#include "handle_base.h"
#include "wait_result.h"

// 仮：自前ハンドル解決
extern HandleEntry* ResolveHandle(void* h);

DWORD WinWaitForSingleObject(void* h, DWORD timeout)
{
    auto entry = ResolveHandle(h);
    if (!entry) {
        return WAIT_FAILED;
    }

    switch (entry->kind) {
    case HandleKind::Process:
    {
        HANDLE real = (HANDLE)entry->object;
        return WaitForSingleObject(real, timeout);
    }

    case HandleKind::Thread:
    {
        HANDLE real = (HANDLE)entry->object;
        return WaitForSingleObject(real, timeout);
    }

    case HandleKind::Event:
    {
        HANDLE real = (HANDLE)entry->object;
        return WaitForSingleObject(real, timeout);
    }

    case HandleKind::Mutex:
    {
        HANDLE real = (HANDLE)entry->object;
        return WaitForSingleObject(real, timeout);
    }

    case HandleKind::Semaphore:
    {
        HANDLE real = (HANDLE)entry->object;
        return WaitForSingleObject(real, timeout);
    }

    default:
        return WAIT_FAILED;
    }
}
