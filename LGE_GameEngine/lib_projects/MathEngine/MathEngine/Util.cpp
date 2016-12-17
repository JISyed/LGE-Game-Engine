#include "Util.h"

namespace lge
{

	bool Util::isEqual(const float a, const float b, const float epsilon)
	{
		const float tmp = a - b;
		return ((tmp >= -epsilon) && (tmp <= epsilon));
	}

	bool Util::isNotEqual(const float a, const float b, const float epsilon)
	{
		const float tmp = a - b;
		return ((tmp < -epsilon) || (tmp > epsilon));
	}

	bool Util::isOne(const float a, const float epsilon)
	{
		const float tmp = a - 1.0f;
		return ((tmp >= -epsilon) && (tmp <= epsilon));
	}

	bool Util::isNonZero(const float a, const float epsilon)
	{
		return ((a < -epsilon) || (a > epsilon));
	}

	bool Util::isZero(const float a, const float epsilon)
	{
		return ((a >= -epsilon) && (a <= epsilon));
	}

}