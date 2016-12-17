/*****************************************************************************/
/*                                                                           */
/* File: QuatApp.cpp                                                         */
/*                                                                           */
/* Quaternioin Application Class                                             */
/*                                                                           */
/*****************************************************************************/

#include "MathEngine.h"
#include "MathApp.h"
#include <math.h>

namespace lge
{
	// STATIC
	void QuatApp::Slerp(Quat &result, const Quat &source, const Quat &target, const float slerpFactor)
	{
		/*Quat dest = target;
		float dot = source.dot(target);

		if (dot < 0)
		{
			dot = -dot;
			dest = -dest;
		}

		const float theta = acosf(dot);
		const float sinTheta = sinf(theta);

		result = (source * (sinf((1 - slerpFactor)*theta) / sinTheta)) + (dest * (sinf(slerpFactor*theta) / sinTheta));*/

		Quat	theTarget;

		// Constants.
		const float QUAT_EPSILON = 0.001f;

		float cosom = source.dot(target);
		if (cosom >= 1.0f)
		{
			// do nothing
			result = source;
		}
		else
		{
			// adjust signs if necessary
			if (cosom < 0.0f)
			{
				cosom = -cosom;
				theTarget = -target;
			}
			else
			{
				theTarget = target;
			}

			// If the the source and target are close, we can do a lerp.
			float tarFactor = slerpFactor;
			float srcFactor = 1.0f - slerpFactor;

			// calculate coefficients
			if (cosom < (1.0f - QUAT_EPSILON))
			{
				// Quats are not close enough for a lerp.
				// Calculating coefficients for a slerp.
				const float omega = acosf(cosom);
				const float sinom = 1.0f / sinf(omega);

				srcFactor = sinf(srcFactor * omega) * sinom;
				tarFactor = sinf(tarFactor * omega) * sinom;
			}


			result.set(source[x] * srcFactor + theTarget[x] * tarFactor,
					   source[y] * srcFactor + theTarget[y] * tarFactor,
					   source[z] * srcFactor + theTarget[z] * tarFactor,
					   source[w] * srcFactor + theTarget[w] * tarFactor);
		}
	}

	// STATIC
	void QuatApp::SlerpArray(Quat *result, const Quat *source, const Quat *target, const float slerpFactor, const int numQuats)
	{
		for (int i = 0; i < numQuats; i++)
		{
			QuatApp::Slerp(result[i], source[i], target[i], slerpFactor);
		}
	}
}
/***** END of File QuatApp.cpp ***********************************************/