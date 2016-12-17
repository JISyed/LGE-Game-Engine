#include "..\EngineFoundation\Game.h"
#include "GameObject.h"
#include <math.h>
#include <cassert>
#include <cstring>

#include "GameObjectManager.h"
#include "Transform.h"
#include "GameObjectBehavior.h"
#include "..\GraphicsSystem\Mesh.h"
#include "..\GraphicsSystem\MeshRenderer.h"
#include "..\GraphicsSystem\Material.h"
#include "..\CollisionSystem\BoundingSphere.h"
#include "..\GraphicsSystem\MaterialRegistry.h"
#include "..\GraphicsSystem\MeshRegistry.h"
#include "..\UnpackagerSystem\ResourceUnpacker.h"
#include "..\GraphicsSystem\NullMeshRenderer.h"
//#include "..\AnimationSystem\NullAnimationJointLink.h"
#include "..\AnimationSystem\AnimationSkeleton.h"
#include "..\GraphicsSystem\GpuBufferVao.h"


const float maxOfVec3(const lge::Vect& vect);

// Find the max of 3 numbers
const float maxOf3(const float a, const float b, const float c);



namespace lge
{
	//
	// Static Data
	//

	IdGenerator GameObject::s_idGen;



	//
	// Methods
	//

	GameObject::GameObject(const char* const newName) :
		customMovementBehavior(nullptr),
		parentModelMatrix(new Matrix(IDENTITY)),
		animJointLink(nullptr/*new NullAnimationJointLink()*/),
		animCtrlr(nullptr),
		name(newName),
		ID(GameObject::s_idGen.MakeNewId()),
		shouldRenderBoundingSphere(false),
		shouldRenderMesh(false)
	{
		assert(newName != nullptr);

		this->transform = new Transform();
		this->meshRenderer = new NullMeshRenderer();
		this->boundingSphere = new BoundingSphere();
		this->boundingSphereRenderer = new MeshRenderer(&MaterialRegistry::Find(MaterialName::BoundingSphereInside), &MeshRegistry::Find(MeshName::BoundingSphere), Matrix(IDENTITY));

		// PCS Debugging
		this->setName(newName);
	}

	GameObject::GameObject(Material * const newMaterial, Mesh* const newMesh, const char* const newName) :
		customMovementBehavior(nullptr),
		parentModelMatrix(new Matrix(IDENTITY)),
		animJointLink(nullptr/*new NullAnimationJointLink()*/),
		animCtrlr(nullptr),
		name(newName),
		ID(GameObject::s_idGen.MakeNewId()),
		shouldRenderBoundingSphere(false),
		shouldRenderMesh(true)
	{
		assert(newMaterial != nullptr);
		assert(newMesh != nullptr);
		assert(newName != nullptr);

		this->transform = new Transform();
		this->meshRenderer = new MeshRenderer(newMaterial, newMesh, Matrix(IDENTITY));
		this->boundingSphere = new BoundingSphere();
		this->boundingSphereRenderer = new MeshRenderer(&MaterialRegistry::Find(MaterialName::BoundingSphereInside), &MeshRegistry::Find(MeshName::BoundingSphere), Matrix(IDENTITY));

		// PCS Debugging
		this->setName(newName);
	}

	GameObject::GameObject(Material* const newMaterial, Mesh* const newMesh, const char* const newName, UseUnpacker_t useUnpacker, const char* const boundingSphereName) :
		customMovementBehavior(nullptr),
		parentModelMatrix(new Matrix(IDENTITY)),
		animJointLink(nullptr/*new NullAnimationJointLink()*/),
		animCtrlr(nullptr),
		name(newName),
		ID(GameObject::s_idGen.MakeNewId()),
		shouldRenderBoundingSphere(false),
		shouldRenderMesh(true)
	{
		useUnpacker;

		assert(newMaterial != nullptr);
		assert(newMesh != nullptr);
		assert(newName != nullptr);

		this->transform = new Transform();
		this->meshRenderer = new MeshRenderer(newMaterial, newMesh, Matrix(IDENTITY));
		this->boundingSphere = new BoundingSphere();
		this->boundingSphereRenderer = new MeshRenderer(&MaterialRegistry::Find(MaterialName::BoundingSphereInside), &MeshRegistry::Find(MeshName::BoundingSphere), Matrix(IDENTITY));

		bool sphereLoaded = ResourceUnpacker::ReadBoundingSphere(boundingSphereName, *(this->boundingSphere));
		sphereLoaded;
		assert(sphereLoaded);

		// PCS Debugging
		this->setName(newName);
	}


	GameObject::~GameObject()
	{
		delete this->transform;
		delete this->boundingSphere;
		delete this->parentModelMatrix;

		if (this->animJointLink != nullptr)
		{
			delete this->animJointLink;
		}

		if (this->customMovementBehavior != nullptr)
		{
			delete this->customMovementBehavior;
		}

		if (this->animCtrlr != nullptr)
		{
			delete this->animCtrlr;
		}

		delete this->meshRenderer;
	}

	



	void GameObject::Update()
	{
		// Update Component
		if (this->customMovementBehavior != nullptr)
		{
			this->customMovementBehavior->Update();
		}

		// Update Animation, if any
		if(this->animCtrlr != nullptr)
		{
			this->animCtrlr->Update(Time::GetDeltaTime());
		}

		// Update the transform matrix information
		this->UpdateMatrixData();

		if (this->animCtrlr != nullptr)
		{
			this->animCtrlr->CalculateWorldBoneMats(this->meshRenderer);
		}
	}


	


	void GameObject::Draw()
	{
		const Matrix& modelMatrix = this->transform->GetModelMatrix();
		const Matrix finalMatrix = modelMatrix * *(this->parentModelMatrix);

		static Material* greenSphereMat = &MaterialRegistry::Find(MaterialName::BoundingSphereInside);
		static Material* redSphereMat = &MaterialRegistry::Find(MaterialName::BoundingSphereOutside);
		
		// HACK: Disable fustrum culling!
		//if (this->shouldRenderMesh)
		//{
			// GPU stuff for animation
			if (this->animCtrlr != nullptr)
			{
				GpuBuffer* const globalMatsBuffer = this->animCtrlr->GetGlobalMatricesGpuBuffer();
				Shader* const shader = this->meshRenderer->GetCurrentMaterial()->GetShader();
				shader->MakeActive();
				shader->SetInputBuffer(globalMatsBuffer, "BoneTransforms", false);
			}

			this->boundingSphereRenderer->SetMaterial(greenSphereMat);
			this->meshRenderer->SetModelMatrix(finalMatrix);
			this->meshRenderer->Draw();

			// HACK: Disable joint rendering. Doesn't correspond properly
			//if (this->animJointLink != nullptr)
			//{
			//	GameObject* parentObj = (GameObject*) this->getParent();
			//	const Vect parentPosition = parentObj->GetTransform().GetPositionCopy();
			//	this->animJointLink->DrawJoint(finalMatrix, this->transform->GetPosition(), parentPosition);
			//}
		//}
		//else
		//{
		//	this->boundingSphereRenderer->SetMaterial(redSphereMat);
		//}

		if (this->shouldRenderBoundingSphere)
		{
			const float maxScale = maxOfVec3(this->transform->GetScale());
			const Vect scaleVect(maxScale * this->boundingSphere->GetRadius());

			const Vect newCenter = this->boundingSphere->GetCenter() * finalMatrix;
			const Matrix bM(Matrix(SCALE, scaleVect) * Matrix(TRANS, newCenter));

			this->boundingSphereRenderer->SetModelMatrix(bM);
			this->boundingSphereRenderer->Draw();
		}
	}







	Transform& GameObject::GetTransform()
	{
		return *(this->transform);
	}


	void GameObject::SetCustomMovementBehavior(GameObjectBehavior* const newBehavior)
	{
		this->customMovementBehavior = newBehavior;
	}


	void GameObject::SetMaterial(Material * const newMaterial)
	{
		this->meshRenderer->SetMaterial(newMaterial);
	}


	void GameObject::SetMesh(Mesh * const newMesh)
	{
		this->meshRenderer->SetMesh(newMesh);
	}





	const unsigned int GameObject::GetId() const
	{
		return this->ID;
	}


	const CString& GameObject::GetName() const
	{
		return this->name;
	}


	// Update the matrix data for this GameObject (local and parent model)
	// Should only ever be called once per frame! (after Update())
	void GameObject::UpdateMatrixData()
	{
		// Set the transform in accordance to an animation joint, if any
		// This will do nothing if there isn't a joint assigned
		if (this->animJointLink != nullptr)
		{
			this->animJointLink->ApplyJointOntoTransform(*(this->transform));
		}

		// Update local model matrix
		this->transform->CalculateModelMatrix();

		// Update parent model matrix
		{
			GameObject* parentObj = (GameObject*) this->getParent();
			if (parentObj != nullptr)
			{
				*(this->parentModelMatrix) = parentObj->GetTransform().GetModelMatrix() * *(parentObj->parentModelMatrix);
			}
		}
	}


	// Get BoundingSphere
	const BoundingSphere& GameObject::GetBoundingSphere() const
	{
		return *(this->boundingSphere);
	}

	// Set BoundingSphere
	void GameObject::SetBoundingSphere(const BoundingSphere& newSphere)
	{
		*(this->boundingSphere) = newSphere;
	}

	// Sends a new corrected BoundingSphere to factor in the position and scale of this GameObject
	const BoundingSphere GameObject::GetCorrectedBoundingSphere() const
	{
		BoundingSphere correctedSphere(*(this->boundingSphere));
		const Matrix& modelMatrix = this->transform->GetModelMatrix();

		correctedSphere.SetRadius( maxOfVec3(this->transform->GetScale()) * this->boundingSphere->GetRadius() );
		correctedSphere.SetCenter(this->boundingSphere->GetCenter() * (modelMatrix * *(this->parentModelMatrix)));

		return correctedSphere;
	}

	// Does this GameObject render its bounding sphere?
	const bool GameObject::DoesRenderBoundingSphere() const
	{
		return this->shouldRenderBoundingSphere;
	}

	// Set whether this GameObject should render its bounding sphere or not
	void GameObject::SetRenderBoundingSphere(const bool shouldRender)
	{
		this->shouldRenderBoundingSphere = shouldRender;
	}


	// Returns true if this GameObject will be drawn
	const bool GameObject::DoesRender() const
	{
		return this->shouldRenderMesh;
	}

	// Set if this GameObject will render or not
	void GameObject::SetIfWillRender(const bool willRender)
	{
		this->shouldRenderMesh = willRender;
	}


	// Set the AnimationJoint for this GameObject
	void GameObject::SetAnimationJoint(const AnimationJoint& newJoint, const float boneScale)
	{
		assert(this->animJointLink == nullptr);
		//delete this->animJointLink;
		//this->animJointLink = nullptr;
		this->animJointLink = new AnimationJointLink(newJoint, boneScale);
	}


	// Add an animation to this GameObject based off an animation set.
	// Automatically adds an animation controller
	void GameObject::AddAnimation(const AnimationSet& animationData, const float boneScale)
	{
		// First create the animation controller from the given set
		assert(this->animCtrlr == nullptr);
		this->animCtrlr = new AnimationController(animationData);

		// Now for every joint in the skeleton, make a child GameObject as a joint
		
		// Get hierarchy information
		const AnimationSkeleton* const skeleton = animationData.GetSkeleton();
		const JointHierarchyTable* const hierarchy = skeleton->GetSkeletonHierarchyData();
		const JointNameTable* const jointNames = skeleton->GetJointNames();
		const KeyFrame& referenceFrame = this->animCtrlr->GetFinalMix();
		const unsigned int numberOfJoints = skeleton->GetNumberOfJoints();
		assert(numberOfJoints != 0);

		// Create joint gameObjects to be added to the manager later
		GameObject** joints = new GameObject*[numberOfJoints];

		// Add the first joint, since it will be the root of the hiearchy
		assert(hierarchy->GetParentIndexOf(0) == LGE_INVALID_JOINT_PARENT);
		joints[0] = new GameObject(jointNames->GetNameOf(0).GetString());
		//joints[0]->SetAnimationJoint(referenceFrame.GetReadOnlyJointAt(0), boneScale);
		GameObjectManager::Add(joints[0], this);

		// Now create every other joint an construct a "skeleton" of joint-GameObjects
		for (unsigned int i = 1; i < numberOfJoints; i++)
		{
			joints[i] = new GameObject(jointNames->GetNameOf(i).GetString());
			joints[i]->SetAnimationJoint(referenceFrame.GetReadOnlyJointAt(i), boneScale);
			GameObjectManager::Add(joints[i], joints[hierarchy->GetParentIndexOf(i)]);
		}

		// Delete the array of pointers. The pointers themselves should not get deleted
		delete[] joints;
	}

	// Get the animation controller of this GameObject, if any
	AnimationController* const GameObject::GetAnimationController() const
	{
		return this->animCtrlr;
	}


}


const float maxOfVec3(const lge::Vect& vect)
{
	return maxOf3(vect.x(), vect.y(), vect.z());
}

// From stack overflow
const float maxOf3(const float a, const float b, const float c)
{
	float m = a;
	(void)((m < b) && (m = b)); //these are not conditional statements.
	(void)((m < c) && (m = c)); //these are just boolean expressions.
	return m;
}


