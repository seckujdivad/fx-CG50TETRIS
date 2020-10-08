#pragma once

#include <stdlib.h>

#define nullptr (void*)0

void* operator new(size_t size);
void operator delete(void* pointer);
void operator delete(void* pointer, size_t size);

int RTC_rand(int ceil);
int RTC_rand(int floor, int ceil);