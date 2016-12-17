#ifndef ENGINE_MATH_UTIL_H
#define ENGINE_MATH_UTIL_H

#include "Constants.h"

namespace lge
{
	// Float equivalance utility functions
	class Util
	{
	public:
		// f1 == f2
		static bool isEqual(const float a, const float b, const float epsilon = MATH_TOLERANCE);
		
		// f1 != f2
		static bool isNotEqual(const float a, const float b, const float epsilon = MATH_TOLERANCE);
		
		// f1 == 1.0f
		static bool isOne(const float a, const float epsilon = MATH_TOLERANCE);
		
		// f1 != 0.0f
		static bool isNonZero(const float a, const float epsilon = MATH_TOLERANCE);
		
		// f1 == 0.0f
		static bool isZero(const float a, const float epsilon = MATH_TOLERANCE);
	};
}
#endif