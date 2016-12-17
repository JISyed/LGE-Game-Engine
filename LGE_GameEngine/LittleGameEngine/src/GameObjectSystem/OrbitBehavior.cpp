#include "OrbitBehavior.h"
#include <math.h>
#include "..\EngineUtilities\Time.h"

#include "MathEngine.h"
#include "Transform.h"

namespace lge
{

	//
	// Ctor / Dtor
	//

	OrbitBehavior::OrbitBehavior(const Transform& target, Transform& our, const float orbitalDist, const float orbitalSpeed) :
		//ourModelView(ourMv),
		//targetModelView(targetMv),
		ourTransform(our),
		targetTransform(target),
		currRotAngle(0.0f),
		orbitDistance(orbitalDist),
		orbitSpeed(orbitalSpeed)
	{
	}

	OrbitBehavior::~OrbitBehavior()
	{
	}



	//
	// Lifetime Methods
	//

	void OrbitBehavior::Update()
	{
		this->currRotAngle += this->orbitSpeed * Time::GetDeltaTimeInSeconds();
		if (this->currRotAngle > MATH_2PI)
		{
			this->currRotAngle = 0.0f;
		}

		//const Matrix RotY(ROT_Y, currRotAngle);
		
		// X orbits, Y Spins, Z also orbits
		//const Matrix TransA(TRANS, 0.0f, 0.0f, this->orbitDistance);
		//this->ourModelView = TransA * RotY * this->targetModelView;

		//this->ourTransform = this->targetTransform;
		this->ourTransform.SetPosition(this->targetTransform.GetPosition());
		this->ourTransform.SetEulerAngles(this->targetTransform.GetEulerAngles());

		const float xRot = this->ourTransform.GetEulerAngles().x();
		const float zRot = this->ourTransform.GetEulerAngles().z();

		

		this->ourTransform.SetEulerAngles(Vect(xRot, currRotAngle, zRot));

		Vect newPosition = this->targetTransform.GetPosition() + Vect(this->orbitDistance, 0.0f, 1.0f);
		this->ourTransform.SetPosition(newPosition);
		
	}

}

