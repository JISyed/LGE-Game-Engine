/*
 * Timer_win32.cpp
 *
 * Timer implementation specific to the win32 platform.
 */

//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include "Timer.h"
#include <windows.h>

namespace lge
{
	//---------------------------------------------------------------------------
	// NATIVE IMPLEMENTATION (WINDOWS):
	//---------------------------------------------------------------------------
	const TimeUnit Timer::getSystemTime()
	{
		const static TimeUnit oneSecond(DurationBasis::OneSecond);

		TimeUnit systemTime;

		LARGE_INTEGER counterStruct;
		LARGE_INTEGER frequencyStruct;

		if (0 != QueryPerformanceCounter(&counterStruct) && 0 != QueryPerformanceFrequency(&frequencyStruct))
		{
			const LONGLONG counter = counterStruct.QuadPart;
			const LONGLONG frequency = frequencyStruct.QuadPart;

			if (counter >= 0 && 0 != frequency)
			{
				const int numSeconds = static_cast<int>(counter / frequency);
				const float remainder = static_cast<float>(counter % frequency);

				systemTime = numSeconds * oneSecond;
				systemTime += (remainder / frequency) * oneSecond;
			}
		}

		return(systemTime);
	}

}