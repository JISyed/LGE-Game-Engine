/*
 * Timer.cpp
 *
 * Common timer implementation across all platforms.
 */

//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include "Timer.h"

namespace lge
{
	//---------------------------------------------------------------------------
	// CONSTRUCTORS / DESTRUCTORS / ASSIGNMENT:
	//---------------------------------------------------------------------------
	Timer::Timer() : 
		_ticMark(DurationBasis::TimeMax)
	{
	}


	Timer::~Timer()
	{
	}


	//---------------------------------------------------------------------------
	// TIMING METHODS:
	//---------------------------------------------------------------------------
	void Timer::tic()
	{
		this->_ticMark = Timer::getSystemTime();
	}


	const TimeUnit Timer::toc() const
	{
		TimeUnit elapsedTime;

		// If tick has been called...
		if (TimeUnit(DurationBasis::TimeMax) != this->_ticMark)
		{
			elapsedTime = Timer::getSystemTime() - this->_ticMark;
		}
		// else elapsed time is already 0

		return elapsedTime;
	}

}