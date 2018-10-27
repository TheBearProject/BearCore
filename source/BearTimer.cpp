﻿#include "BearCore.hpp"
#include <time.h>
#include <ctime>
LARGE_INTEGER getFrequency()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}
BearCore::BearTime BearCore::BearTimer::getCurrentTime() const
{
	HANDLE currentThread = GetCurrentThread();
	DWORD_PTR previousMask = SetThreadAffinityMask(currentThread, 1);

	static LARGE_INTEGER frequency = getFrequency();

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	SetThreadAffinityMask(currentThread, previousMask);
	
	return /*BearCore::BearTime(int32(std::clock()));*/BearTime(1000000 * time.QuadPart / frequency.QuadPart);
}