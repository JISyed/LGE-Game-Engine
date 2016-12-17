#ifndef H_LGE_ANIMATION_JOINT
#define H_LGE_ANIMATION_JOINT

#include "MathEngine.h"

namespace lge
{
	// A single joint in a skeletal animation. Sometimes called Bone
	struct AnimationJoint : public Align16
	{
		Vect Translation;	// The position of the joint
		Quat Rotation;		// The orientation of the joint
		Vect Scale;			// The scaling of the joint


		//
		// Methods
		//

		// Default Ctor
		AnimationJoint();
		// Copy Ctor
		AnimationJoint(const AnimationJoint& other);
		// Copy Assignment
		AnimationJoint& operator=(const AnimationJoint& other);
		// Dtor
		~AnimationJoint();
	};
}
#endif