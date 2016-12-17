#ifndef H_LGE_ANIMATION_JOINT_LINK
#define H_LGE_ANIMATION_JOINT_LINK
#include "AnimationJoint.h"

namespace lge
{
	class Transform;
	class MeshRenderer;
	class Matrix;

	// A link for an AnimationJoint to alter a joint-GameObject transform
	class AnimationJointLink
	{
	public:

		// Ctor  
		AnimationJointLink(const AnimationJoint& newJoint, const float newBoneScale = 1.0f);
		// Dtor
		virtual ~AnimationJointLink();


		// Apply the joint on the given transform
		void ApplyJointOntoTransform(Transform& transform) const;

		// Draw the joint, if drawing is enabled
		void DrawJoint(const Matrix& worldJointMatrix, const Vect& worldJointPositon, const Vect& worldParentPosition);


	private:

		//
		// Data
		//

		const AnimationJoint& joint;
		MeshRenderer* jointRenderer;
		float boneScale;
		bool shouldRender;



		//
		// Deleted Methods
		//

		AnimationJointLink() = delete;
		AnimationJointLink(const AnimationJointLink& other) = delete;
		AnimationJointLink& operator=(const AnimationJointLink& other) = delete;
	};
}
#endif