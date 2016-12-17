#ifndef ENGINE_TIMEUNIT_H
#define ENGINE_TIMEUNIT_H

namespace lge
{
	// Represents one of the basic spans of time to set as a default value for a new TimeUnit
	enum class DurationBasis : unsigned int
	{
		/* For constructing a Time of zero. */
		Zero,

		/* For constructing one NTSC 60 hz frame of TimeUnit. */
		Ntsc60Frame,

		/* For constructing half of an NTSC 60 hz frame of TimeUnit. */
		Ntsc30Frame,

		/* For constructing one PAL 50 hz frame of TimeUnit. */
		PalFrame,

		/* For constructing one millisecond of TimeUnit. */
		OneMillisecond,

		/* For constructing one second of TimeUnit. */
		OneSecond,

		/* For constructing one minute of TimeUnit. */
		OneMinute,

		/* For constructing one hour of TimeUnit. */
		OneHour,

		/*
		 * For constructing the most <i>negative</i> TimeUnit
		 * that can be represented.
		 */
		TimeMin,

		/*
		 * For constructing the most positive Time
		 * that can be represented.
		 */
		TimeMax
	};


	//---------------------------------------------------------------------------
	// CLASS DECLARATION:
	//---------------------------------------------------------------------------

	// Can represent either a point in time or a span of time
	class TimeUnit
	{

	public:

		//-----------------------------------------------------------------
		// Friends
		//-----------------------------------------------------------------

		/*
		* return: The product of the specified float and TimeUnit.
		*
		* Example:
		*    const TimeUnit halfSecond = 0.5f * TimeUnit(ONE_SECOND);
		*/
		friend const TimeUnit operator*(const float ratio, const TimeUnit & rhs);

		/*
		* return: The product of the specified integer and TimeUnit.
		*
		* Example:
		*    const TimeUnit fourMinutes = 4 * TimeUnit(ONE_MINUTE);
		*/
		friend const TimeUnit operator*(const int ratio, const TimeUnit & rhs);

		//-----------------------------------------------------------------
		// Constructors / Destructors / Assignment
		//-----------------------------------------------------------------

		/* Creates a TimeUnit equal to TimeUnit(ZERO). */
		inline TimeUnit();

		/*
		* Creates the specific amount of Time.
		*
		* Example:
		*    const TimeUnit oneSecond( ONE_SECOND );
		*/
		explicit TimeUnit(const DurationBasis duration);

		/* Creates a copy of the specified TimeUnit. */
		inline TimeUnit(const TimeUnit& rhs);

		/*
		* Assigns the right-hand side to this TimeUnit.
		* return: this TimeUnit.
		*
		*  Example:
		*    const TimeUnit tickDuration = TimeUnit(NTSC_DURATION);
		*/
		inline TimeUnit& operator=(const TimeUnit& rhs);

		// destrutor
		~TimeUnit()
		{
		}

		//-----------------------------------------------------------------
		// Comparisons
		//-----------------------------------------------------------------

		/*
		* return: true if this TimeUnit is equal to the right-hand side.
		*
		*  Example:
		*    assert( TimeUnit(ONE_HOUR)   == 60 * TimeUnit(ONE_MINUTE) );
		*    assert( TimeUnit(ONE_MINUTE) == 60 * TimeUnit(ONE_SECOND) );
		*/
		bool operator==(const TimeUnit& rhs) const;

		/*
		* return: true if this TimeUnit is not equal to the right-hand side.
		*/
		bool operator!=(const TimeUnit& rhs) const;

		/*
		* return: true if this TimeUnit is less than the right-hand side.
		*
		* Example:
		*    bool couldBeOttosMileTime( const TimeUnit t )
		*    {
		*       return( t < 4 * TimeUnit(ONE_MINUTE) );
		*    }
		*/
		bool operator<(const TimeUnit& rhs) const;

		/*
		* return: true if this TimeUnit is less or equal to the right-hand side.
		*/
		bool operator<=(const TimeUnit& rhs) const;

		/*
		* return: true if this TimeUnit is greater than the right-hand side.
		*/
		bool operator>(const TimeUnit& rhs) const;

		/*
		* return: true if this TimeUnit is greather than or equal to
		*  the right-hand side.
		*/
		bool operator>=(const TimeUnit& rhs) const;

		//-----------------------------------------------------------------
		// Negation / Addition / Subtraction
		//-----------------------------------------------------------------

		/*
		* return: A negative copy of this TimeUnit.
		*
		* Example:
		*    void neverFail( const TimeUnit t )
		*    {
		*       assert( t + (-t) == TimeUnit(ZERO) );
		*    }
		*/
		const TimeUnit operator-() const;

		/*
		* return: The sum of this TimeUnit and the right-hand side.
		*
		* Example:
		*    void neverFail( const TimeUnit t )
		*    {
		*       assert( t + t == 2 * t );
		*    }
		*/
		const TimeUnit operator+(const TimeUnit& rhs) const;

		/*
		* return: The difference between this TimeUnit and the right-hand side.
		*
		* Example:
		*    void neverFail( const TimeUnit t )
		*    {
		*       assert( t - t == TimeUnit(ZERO) );
		*    }
		*/
		const TimeUnit operator-(const TimeUnit& rhs) const;

		/*
		* Adds the right-hand side to this TimeUnit.
		*
		* return: This TimeUnit.
		*
		*  Example:
		*    void zeroOutTime( TimeUnit& t )
		*    {
		*       t += (-t);
		*       assert( TimeUnit(ZERO) == t );
		*    }
		*/
		TimeUnit& operator+=(const TimeUnit& rhs);

		/*
		* Subtracts the right-hand side from this TimeUnit.
		*
		* return: This TimeUnit.
		*
		*  Example:
		*    void zeroOutTime( TimeUnit& t )
		*    {
		*       t -= t;
		*       assert( TimeUnit(ZERO) == t );
		*    }
		*/
		TimeUnit& operator-=(const TimeUnit& rhs);

		//-----------------------------------------------------------------
		// Multiplication
		//-----------------------------------------------------------------

		/*
		* return: The product of this TimeUnit and the specified float.
		*
		* Example:
		*    const TimeUnit halfSecond = TimeUnit(ONE_SECOND) * 0.5f;
		*/
		const TimeUnit operator*(const float ratio) const;

		/*
		* return: The product of this TimeUnit and the specified integer.
		*
		*  Example:
		*    const TimeUnit fourMinutes = TimeUnit(ONE_MINUTE) * 4;
		*/
		const TimeUnit operator*(const int ratio) const;

		/*
		* Multiplies this TimeUnit by the specified float.
		*
		* return: This TimeUnit.
		*
		* Example:
		*    void decayTime( TimeUnit& t )
		*    {
		*       t *= 0.95f;
		*    }
		*/
		TimeUnit& operator*=(const float ratio);

		/*
		* Multiplies this Time by the specified integer.
		*
		* return: This TimeUnit.
		*
		* Example:
		*    void doubleTime( TimeUnit& t )
		*    {
		*       t *= 2;
		*    }
		*/
		TimeUnit& operator*=(const int ratio);

		//-----------------------------------------------------------------
		// name: Division
		//-----------------------------------------------------------------

		/*
		* return: The ratio of this TimeUnit divided by the denominator TimeUnit.
		*
		* note: Dividing by TimeUnit::ZERO is undefined.
		*/
		float operator/(const TimeUnit& denominator) const;

		/*
		* return: The result of dividing this TimeUnit and by the
		* specified float.
		*
		* note: Dividing by zero is undefined.
		*/
		const TimeUnit operator/(const float denominator) const;

		/*
		* return: The result of dividing this TimeUnit by the
		* specified integer.
		*
		* note: Dividing by zero is undefined.
		*/
		const TimeUnit operator/(const int denominator) const;

		/*
		* Divides this TimeUnit by the specified float.
		*
		* return: This TimeUnit.
		*
		* note: Dividing by zero is undefined.
		*/
		TimeUnit& operator/=(const float denominator);

		/*
		* Divides this TimeUnit by the specified integer.
		*
		* return: This TimeUnit.
		*
		* note: Dividing by zero is undefined.
		*/
		TimeUnit& operator/=(const int denominator);

		//-----------------------------------------------------------------
		// Quotient / Remainder
		//-----------------------------------------------------------------

		/*
		* return: The truncated, integral division of the
		* numerator and denominator.  In other words,
		* the result of the division is rounded down to the nearest
		* integer.
		*
		* note: Dividing by TimeUnit(ZERO) is undefined.
		*/
		static int quotient(const TimeUnit& numerator, const TimeUnit& denominator);

		/*
		* return: The remainder of dividing the numerator into the
		* denominator.  This is the equivalent of a modulus operation.
		*
		* note: Dividing by TimeUnit(ZERO) is undefined.
		*/
		static const TimeUnit remainder(const TimeUnit& numerator, const TimeUnit& denominator);

	private:
		// Internal representation of time keeping (must be signed)
		typedef int Representation;

		// constructor
		explicit TimeUnit(const Representation rawTime);

		// data
		Representation _rawTime;
	};




	//---------------------------------------------------------------------------
	// INLINED IMPLEMENTATION:
	//---------------------------------------------------------------------------
	TimeUnit::TimeUnit() : _rawTime(0)
	{
	}


	TimeUnit::TimeUnit(const TimeUnit& rhs) : _rawTime(rhs._rawTime)
	{
	}


	TimeUnit& TimeUnit::operator=(const TimeUnit& rhs)
	{
		if (this != &rhs)
		{
			this->_rawTime = rhs._rawTime;
		}

		return(*this);
	}


}
#endif