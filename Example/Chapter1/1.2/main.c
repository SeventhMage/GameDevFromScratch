#include <stdio.h>
#include <assert.h>
#include "gmemory.h"

int main(int argc, char *argv[])
{
    void *ptr = CreateMemoryZone(1024 * 1024);
    DebugPrint(ptr, "init");
    void *alloc1 = Malloc(ptr, 1024);
    void *alloc2 = Malloc(ptr, 32);
    void *alloc3 = Malloc(ptr, 100);
    assert(alloc1);
    assert(alloc2);
    assert(alloc3);
    DebugPrint(ptr, "alloc 64 32 100");
    Free(ptr, alloc2);
    DebugPrint(ptr, "free 2");
    Free(ptr, alloc1);
    DebugPrint(ptr, "free 1");
    Free(ptr, alloc3);
    DebugPrint(ptr, "free 3");
    DestroyMemoryZone(ptr);
    return 0;
}
