// TimeUnit.cpp

//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include "TimeUnit.h"
#include <limits>   // For numeric_limits< Time::Representation >.

namespace lge
{
	//---------------------------------------------------------------------------
	// FRIENDS:
	//---------------------------------------------------------------------------
	const TimeUnit operator*(const float ratio, const TimeUnit& rhs)
	{
		return TimeUnit(static_cast<TimeUnit::Representation>(ratio * rhs._rawTime));
	}

	const TimeUnit operator*(const int ratio, const TimeUnit& rhs)
	{
		return TimeUnit(ratio * rhs._rawTime);
	}



	//---------------------------------------------------------------------------
	// CONSTRUCTORS:
	//---------------------------------------------------------------------------

	TimeUnit::TimeUnit(const DurationBasis duration) :
		_rawTime(0)
	{
		// IMPORTANT: This is private information that is SUBJECT TO CHANGE!
		//
		// Currently: 1 second = 30000
		//            1 ms     = 30
		//            1 NTSC   = 500
		//            1 PAL    = 600
		//
		// At 32 bits, this gives us a range of roughly -20 to 20 hours.
		const TimeUnit::Representation ONE_RAW_SECOND = 30000;

		switch (duration)
		{
			case DurationBasis::Zero:
				this->_rawTime = 0;
				break;

			case DurationBasis::Ntsc60Frame:
				this->_rawTime = ONE_RAW_SECOND / 60;
				break;

			case DurationBasis::Ntsc30Frame:
				this->_rawTime = 2 * ONE_RAW_SECOND / 60;
				break;

			case DurationBasis::PalFrame:
				this->_rawTime = ONE_RAW_SECOND / 50;
				break;

			case DurationBasis::OneSecond:
				this->_rawTime = ONE_RAW_SECOND;
				break;

			case DurationBasis::OneMillisecond:
				this->_rawTime = ONE_RAW_SECOND / 1000;
				break;

			case DurationBasis::OneMinute:
				this->_rawTime = 60 * ONE_RAW_SECOND;
				break;

			case DurationBasis::OneHour:
				this->_rawTime = 60 * 60 * ONE_RAW_SECOND;
				break;

			case DurationBasis::TimeMin:
				this->_rawTime = std::numeric_limits< TimeUnit::Representation >::min();
				break;

			case DurationBasis::TimeMax:
				this->_rawTime = std::numeric_limits< TimeUnit::Representation >::max();
				break;

			default:
				// IMPORTANT: Intentionally avoiding assertion handling
				//            for the Time library.
				this->_rawTime = 0;
				break;
		}
	}



	//---------------------------------------------------------------------------
	// COMPARISONS:
	//---------------------------------------------------------------------------
	bool TimeUnit::operator==(const TimeUnit& rhs) const
	{
		return(this->_rawTime == rhs._rawTime);
	}


	bool TimeUnit::operator!=(const TimeUnit& rhs) const
	{
		return(this->_rawTime != rhs._rawTime);
	}


	bool TimeUnit::operator<(const TimeUnit& rhs) const
	{
		return(this->_rawTime < rhs._rawTime);
	}


	bool TimeUnit::operator<=(const TimeUnit& rhs) const
	{
		return(this->_rawTime <= rhs._rawTime);
	}


	bool TimeUnit::operator>(const TimeUnit& rhs) const
	{
		return(this->_rawTime > rhs._rawTime);
	}


	bool TimeUnit::operator>=(const TimeUnit& rhs) const
	{
		return(this->_rawTime >= rhs._rawTime);
	}



	//---------------------------------------------------------------------------
	// NEGATION / ADDITION / SUBTRACTION:
	//---------------------------------------------------------------------------
	const TimeUnit TimeUnit::operator-() const
	{
		return(TimeUnit(-this->_rawTime));
	}


	const TimeUnit TimeUnit::operator+(const TimeUnit& rhs) const
	{
		// !!! FIXME: Overflow checks
		return(TimeUnit(this->_rawTime + rhs._rawTime));
	}


	const TimeUnit TimeUnit::operator-(const TimeUnit& rhs) const
	{
		// !!! FIXME: Overflow checks
		return(TimeUnit(this->_rawTime - rhs._rawTime));
	}


	TimeUnit& TimeUnit::operator+=(const TimeUnit& rhs)
	{
		// !!! FIXME: Overflow checks
		this->_rawTime += rhs._rawTime;
		return(*this);
	}


	TimeUnit& TimeUnit::operator-=(const TimeUnit& rhs)
	{
		// !!! FIXME: Overflow checks
		this->_rawTime -= rhs._rawTime;
		return(*this);
	}



	//---------------------------------------------------------------------------
	// MULTIPLICATION:
	//---------------------------------------------------------------------------
	const TimeUnit TimeUnit::operator*(const float ratio) const
	{
		// !!! FIXME: Overflow checks
		return TimeUnit(static_cast<Representation>(ratio * this->_rawTime));
	}


	const TimeUnit TimeUnit::operator*(const int ratio) const
	{
		// !!! FIXME: Overflow checks
		return(TimeUnit(this->_rawTime * ratio));
	}


	TimeUnit& TimeUnit::operator*=(const float ratio)
	{
		// !!! FIXME: Overflow checks
		this->_rawTime = static_cast<Representation>(ratio * this->_rawTime);
		return(*this);
	}


	TimeUnit& TimeUnit::operator*=(const int ratio)
	{
		// !!! FIXME: Overflow checks
		this->_rawTime *= ratio;
		return(*this);
	}



	//---------------------------------------------------------------------------
	// DIVISION:
	//---------------------------------------------------------------------------
	float TimeUnit::operator/(const TimeUnit& denominator) const
	{
		// !!! FIXME: Divide by zero.
		return static_cast<float>(this->_rawTime) / static_cast<float>(denominator._rawTime);
	}


	const TimeUnit TimeUnit::operator/(const float denominator) const
	{
		// !!! FIXME: Divide by zero.
		return TimeUnit(static_cast<Representation>(this->_rawTime / denominator));
	}


	const TimeUnit TimeUnit::operator/(const int denominator) const
	{
		// !!! FIXME: Divide by zero.
		return TimeUnit(this->_rawTime / denominator);
	}


	TimeUnit& TimeUnit::operator/=(const float denominator)
	{
		// !!! FIXME: Divide by zero.
		this->_rawTime = static_cast<Representation>(this->_rawTime / denominator);
		return(*this);
	}


	TimeUnit& TimeUnit::operator/=(const int denominator)
	{
		// !!! FIXME: Divide by zero.
		this->_rawTime /= denominator;
		return(*this);
	}



	//---------------------------------------------------------------------------
	// DIVISION:
	//---------------------------------------------------------------------------
	int TimeUnit::quotient(const TimeUnit& numerator, const TimeUnit& denominator)
	{
		// !!! FIXME: Divide by zero & check range
		return static_cast<int> (numerator._rawTime / denominator._rawTime);
	}


	const TimeUnit TimeUnit::remainder(const TimeUnit& numerator, const TimeUnit& denominator)
	{
		// !!! FIXME: Divide by zero.
		return TimeUnit(numerator._rawTime % denominator._rawTime);
	}


	//---------------------------------------------------------------------------
	// PRIVATE IMPLEMENTATION:
	//---------------------------------------------------------------------------
	TimeUnit::TimeUnit(const TimeUnit::Representation rawTime) :
		_rawTime(rawTime)
	{
	}

}