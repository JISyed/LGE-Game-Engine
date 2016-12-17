#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "..\PCS\PCSNode.h"
#include "..\EngineUtilities\IdGenerator.h"
#include "..\UnpackagerSystem\enumUseUnpackerType.h"
#include "..\AbstractDataTypes\CString.h"
#include "..\AnimationSystem\AnimationJointLink.h"
#include "..\AnimationSystem\AnimationController.h"

namespace lge
{
	// Foward declares
	class Transform;
	class GameObjectBehavior;
	class Material;
	class Mesh;
	class MeshRenderer;
	class BoundingSphere;
	class Matrix;

	// Represents an entity in the game. Can be used for play or regulation of the game
	class GameObject final : public PCSNode
	{
	public:

		//
		// Ctor / Dtor
		//

		explicit GameObject(const char* const newName);
		GameObject(Material* const newMaterial, Mesh* const newMesh, const char* const newName);
		GameObject(Material* const newMaterial, Mesh* const newMesh, const char* const newName, UseUnpacker_t useUnpacker, const char* const boundingSphereName);
		~GameObject();



		//
		// Lifetime Methods
		//

		// Update object logic every frame
		void Update();

		// Draw object every frame
		void Draw();




		//
		// Other Methods
		//
		
		// Get the transform data for this GameObject
		Transform& GetTransform();

		// Set the behavior for movement of this GameObject
		void SetCustomMovementBehavior(GameObjectBehavior* const newBehavior);

		// Change the material of this GameObject
		void SetMaterial(Material* const newMaterial);

		// Change the mesh of this GameObject
		void SetMesh(Mesh* const newMesh);

		// Get the ID of this GameObject
		const unsigned int GetId() const;

		// Get the name of this GameObject
		const CString& GetName() const;

		// Get BoundingSphere
		const BoundingSphere& GetBoundingSphere() const;

		// Set BoundingSphere
		void SetBoundingSphere(const BoundingSphere& newSphere);

		// Sends a new corrected BoundingSphere to factor in the position and scale of this GameObject
		const BoundingSphere GetCorrectedBoundingSphere() const;

		// Does this GameObject render its bounding sphere?
		const bool DoesRenderBoundingSphere() const;

		// Set whether this GameObject should render its bounding sphere or not
		void SetRenderBoundingSphere(const bool shouldRender);

		// Returns true if this GameObject will be drawn
		const bool DoesRender() const;

		// Set if this GameObject will render or not
		void SetIfWillRender(const bool willRender);

		// Add an animation to this GameObject based off an animation set.
		// Automatically adds an animation controller
		void AddAnimation(const AnimationSet& animationData, const float boneScale);

		// Get the animation controller of this GameObject, if any
		AnimationController* const GetAnimationController() const;

		


	private:

		//
		// Data
		//
		
		Transform* transform;
		GameObjectBehavior* customMovementBehavior;
		MeshRenderer* meshRenderer;
		BoundingSphere* boundingSphere;
		MeshRenderer* boundingSphereRenderer;
		Matrix* parentModelMatrix;
		AnimationJointLink* animJointLink;
		AnimationController* animCtrlr;
		CString name;
		unsigned int ID;
		bool shouldRenderBoundingSphere;
		bool shouldRenderMesh;


		//
		// Static Data
		//

		static IdGenerator s_idGen;



		//
		// Private Routines
		//

		// Update the matrix data for this GameObject (local and parent model)
		// Should only ever be called once per frame! (after Update())
		void UpdateMatrixData();

		// Set the AnimationJoint for this GameObject
		void SetAnimationJoint(const AnimationJoint& newJoint, const float boneScale);



		//
		// Deleted Methods
		//

		// No default ctor
		GameObject() = delete;

		// No copy ctor
		GameObject(const GameObject& other) = delete;

		// No copy assignment
		GameObject& operator=(const GameObject& other) = delete;

		// No move ctor
		GameObject(GameObject&& other) = delete;

		// No move assignment
		GameObject& operator=(GameObject&& other) = delete;
	};
}


#endif