#pragma once

#include <stddef.h>
#include <stdlib.h>

void* operator new(size_t size);
void* operator new[](size_t size);

void operator delete(void* pointer);
void operator delete[](void* pointer);