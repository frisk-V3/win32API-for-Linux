#include "win_event.hpp"
#include "handle_base.h"

extern void* AllocateHandle(HandleKind kind, void* obj);

void* WinCreateEvent(bool manualReset, bool initialState)
{
    WinEvent* ev = new WinEvent(manualReset, initialState);
    return AllocateHandle(HandleKind::Event, ev);
}

bool WinSetEvent(void* h)
{
    auto entry = ResolveHandle(h);
    if (!entry || entry->kind != HandleKind::Event) return false;

    ((WinEvent*)entry->object)->set();
    return true;
}

bool WinResetEvent(void* h)
{
    auto entry = ResolveHandle(h);
    if (!entry || entry->kind != HandleKind::Event) return false;

    ((WinEvent*)entry->object)->reset();
    return true;
}
