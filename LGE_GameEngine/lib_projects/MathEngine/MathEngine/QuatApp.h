
/*****************************************************************************/
/*                                                                           */
/* file: QuatApp.h                                                           */
/*                                                                           */
/*****************************************************************************/

#ifndef QuatApp_H
#define QuatApp_H

#include "Quat.h"

namespace lge
{
	// A collection of special Quaternion operations
	class QuatApp
	{
	public:
		static void Slerp(Quat &result, const Quat &source, const Quat &target, const float slerpFactor);

		static void SlerpArray(Quat *result, const Quat *source, const Quat *target, const float slerpFactor, const int numQuats);
	};
}
#endif 

/**** END of QuatApp.h *******************************************************/
