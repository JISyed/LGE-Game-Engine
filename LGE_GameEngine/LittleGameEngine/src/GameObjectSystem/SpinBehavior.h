#ifndef GAME_OBJECT_BEHAVIOR_SPIN_H
#define GAME_OBJECT_BEHAVIOR_SPIN_H

#include "GameObjectBehavior.h"

namespace lge
{
	// Forward declares
	class Transform;

	// Makes the object perform spin behavior similar to SB6's SpinnyCube demo
	class SpinBehavior final : public GameObjectBehavior
	{
	public:

		//
		// Ctor / Dtor
		//

		SpinBehavior(const float newRotationSpeed, Transform& our);
		virtual ~SpinBehavior();



		//
		// Lifetime Methods
		//

		virtual void Update() override;



	private:


		//
		// Data
		//

		//Matrix& ourModelView;
		Transform& ourTransform;
		float rotationSpeed;



		//
		// Deleted Methods
		//

		// No defualt ctor
		SpinBehavior() = delete;

		// No copy ctor
		SpinBehavior(const SpinBehavior& other) = delete;

		// No assignment overload
		SpinBehavior& operator=(const SpinBehavior& other) = delete;

		// No move ctor
		SpinBehavior(SpinBehavior&& other) = delete;

		// No move assignment
		SpinBehavior& operator=(SpinBehavior&& other) = delete;
	};

}

#endif