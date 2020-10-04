#include "utilities.h"

#include <fxcg/heap.h>

void* __gxx_personality_v0;

void* operator new(size_t size)
{
    return sys_malloc(size);
}

void* operator new[](size_t size)
{
    return sys_malloc(size);
}

void operator delete(void* pointer)
{
    sys_free(pointer);
}

void operator delete[](void* pointer)
{
    sys_free(pointer);
}