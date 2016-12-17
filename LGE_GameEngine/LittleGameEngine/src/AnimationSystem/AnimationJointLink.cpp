#include "AnimationJointLink.h"
#include "..\GameObjectSystem\Transform.h"
#include <cassert>
#include "..\GraphicsSystem\MeshRenderer.h"
#include "..\GraphicsSystem\MeshRegistry.h"
#include "..\GraphicsSystem\MaterialRegistry.h"
#include "MathEngine.h"
#include "MathApp.h"
#include <cmath>

#define LGE_ANIM_ENABLE_JOINT_RENDERING true

namespace lge
{
	AnimationJointLink::AnimationJointLink(const AnimationJoint& newJoint, const float newBoneScale) :
		joint(newJoint),
		jointRenderer(nullptr),
		boneScale(newBoneScale),
		shouldRender(LGE_ANIM_ENABLE_JOINT_RENDERING)
	{
		this->jointRenderer = new MeshRenderer(&MaterialRegistry::Find(MaterialName::Default),
											   &MeshRegistry::Find(MeshName::BoundingSphere),
											   Matrix(IDENTITY));
	}

	// VIRTUAL
	AnimationJointLink::~AnimationJointLink()
	{
		delete this->jointRenderer;
	}


	// VIRTUAL
	// Apply the joint on the given transform
	void AnimationJointLink::ApplyJointOntoTransform(Transform& transform) const
	{
		transform.SetPosition(this->joint.Translation * this->boneScale);
		transform.SetScale(this->joint.Scale);
		transform.SetEulerAngles(this->joint.Rotation);
	}

	// VIRTUAL
	// Draw the joint, if drawing is enabled
	void AnimationJointLink::DrawJoint(const Matrix& worldJointMatrix, const Vect& worldJointPositon, const Vect& worldParentPosition)
	{
		static Mesh& jointMesh = MeshRegistry::Find(MeshName::BoundingSphere);
		static Mesh& boneMesh = MeshRegistry::Find(MeshName::Cube);

		if (this->shouldRender)
		{
			this->jointRenderer->SetMesh(&jointMesh);
			this->jointRenderer->SetModelMatrix(worldJointMatrix);
			this->jointRenderer->Draw();

			worldJointPositon;
			worldParentPosition;
			/*const float difference = std::fabsf(worldParentPosition.mag() - worldJointPositon.mag());
			Matrix boneMatrix = Matrix(MatrixScaleType::SCALE, difference, 0.5f, 0.5f);

			this->jointRenderer->SetMesh(&boneMesh);
			this->jointRenderer->SetModelMatrix(boneMatrix * worldJointMatrix);
			this->jointRenderer->Draw();*/
		}
	}

}