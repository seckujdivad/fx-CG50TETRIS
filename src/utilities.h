#pragma once

#include <stdlib.h>

//#define nullptr 0

void* operator new(size_t size);
void* operator new[](size_t size);

void operator delete(void* pointer);
void operator delete[](void* pointer);
void operator delete(void* pointer, size_t size);

int RTC_rand(int ceil);
int RTC_rand(int floor, int ceil);

template<typename T>
inline T max(T a, T b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

template<typename T>
inline T min(T a, T b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}