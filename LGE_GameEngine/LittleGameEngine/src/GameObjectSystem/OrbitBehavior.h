#ifndef GAME_OBJECT_BEHAVIOR_ORBIT_H
#define GAME_OBJECT_BEHAVIOR_ORBIT_H

#include "GameObjectBehavior.h"

namespace lge
{
	// Forward declares
	class Transform;


	// Allows one object to orbit around another (might get deleted later)
	class OrbitBehavior final : public GameObjectBehavior
	{
	public:

		//
		// Ctor / Dtor
		//

		OrbitBehavior(const Transform& target, Transform& our, const float orbitalDist, const float orbitalSpeed);
		virtual ~OrbitBehavior();




		//
		// Lifetime Methods
		//

		virtual void Update() override;


	private:

		//
		// Data
		//

		//Matrix& ourModelView;				// The model view matrix of the GameObject holding this Behavior
		//const Matrix& targetModelView;		// The model view matrix of the GameObject to be orbited around
		Transform& ourTransform;
		const Transform& targetTransform;
		float currRotAngle;
		float orbitDistance;
		float orbitSpeed;




		//
		// Deleted Methods
		//

		// No defualt ctor
		OrbitBehavior() = delete;

		// No copy ctor
		OrbitBehavior(const OrbitBehavior& other) = delete;

		// No assignment overload
		OrbitBehavior& operator=(const OrbitBehavior& other) = delete;

		// No move ctor
		OrbitBehavior(OrbitBehavior&& other) = delete;

		// No move assignment
		OrbitBehavior& operator=(OrbitBehavior&& other) = delete;
	};

}

#endif