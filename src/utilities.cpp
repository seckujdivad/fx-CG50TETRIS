#include "utilities.h"

#include <fxcg/rtc.h>

void* operator new(size_t size)
{
    return malloc(size);
}

void operator delete(void* pointer)
{
    if (pointer != nullptr)
	{
		free(pointer);
	}
}

void operator delete(void* pointer, size_t size)
{
	if (pointer != nullptr)
	{
		free(pointer);
	}
}

int RTC_rand(int ceil)
{
    return RTC_GetTicks() % ceil;
}

int RTC_rand(int floor, int ceil)
{
    return floor + RTC_rand(ceil - floor);
}