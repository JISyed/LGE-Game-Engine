/*
 *  Timer.cpp
*/

#include <windows.h>
#include <assert.h>

#include"Timer.h"

float timer::SecondsPerCycle = 0.0f;

void timer::initTimer() 
{
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	SecondsPerCycle = 1.0f / Frequency.QuadPart;
}

LARGE_INTEGER timer::getTimer()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return time;
}

void timer::tic()
{
	ticTime = this->getTimer();
}

void timer::toc()
{
	tocTime = this->getTimer();
	assert( tocTime.QuadPart > ticTime.QuadPart );
	deltaTime.QuadPart = tocTime.QuadPart - ticTime.QuadPart;
}

void timer::reset()
{
	ticTime.QuadPart = 0;
	tocTime.QuadPart = 0;
	deltaTime.QuadPart = 0;
}

float timer::timeInSeconds()
{
	float floatTime;
	floatTime = static_cast<float>(deltaTime.QuadPart);
	floatTime *= SecondsPerCycle;
	return floatTime;
}