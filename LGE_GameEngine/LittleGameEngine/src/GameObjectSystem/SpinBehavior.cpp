#include "SpinBehavior.h"
#include <math.h>
#include "..\EngineUtilities\Time.h"

#include "MathEngine.h"
#include "Transform.h"

namespace lge
{
	SpinBehavior::SpinBehavior(const float newRotationSpeed, Transform& our) :
		ourTransform(our),
		rotationSpeed(newRotationSpeed)//,
		//ourModelView(ourMv)
	{
	}

	SpinBehavior::~SpinBehavior()
	{
	}


	void SpinBehavior::Update()
	{
		const float currentTime = Time::GetTimeFromStartInSeconds();
		//const float f = currentTime * this->rotationSpeed;

		//Matrix TransA(TRANS, 0.0f, 0.0f, -24.0f);
		//Matrix TransB(TRANS, sinf(2.1f * f) * 0.5f, cosf(1.7f * f) * 0.5f, sinf(1.3f * f) * cosf(1.5f * f) * 2.0f);
		//Matrix RotY(ROT_Y, ((float)currentTime* this->rotationSpeed * 45.0f) * MATH_PI_180);
		//Matrix RotX(ROT_X, ((float)currentTime* this->rotationSpeed * 81.0f) * MATH_PI_180);

		//this->ourModelView = RotX * RotY * TransB * TransA;

		Vect newEulers(((float)currentTime* this->rotationSpeed * 81.0f) * MATH_PI_180, 
					   ((float)currentTime* this->rotationSpeed * 45.0f) * MATH_PI_180,
					   0.0f
		);
		this->ourTransform.SetEulerAngles(newEulers);

		const Vect newPosition =
			this->ourTransform.GetPosition()
			+ (this->ourTransform.GetRightDirection() * 3.0f * Time::GetDeltaTimeInSeconds())
		;
		this->ourTransform.SetPosition(newPosition);

		
	}

}
