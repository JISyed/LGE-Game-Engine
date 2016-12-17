#include "GameObjectManager.h"
#include <cassert>

#include "Transform.h"
#include "..\EngineUtilities\Time.h"

#include "..\PCS\PCSTreeForwardIterator.h"
#include "..\PCS\PCSTreeReverseIterator.h"

#include "..\GraphicsSystem\MeshRegistry.h"
#include "..\GraphicsSystem\MaterialRegistry.h"

#include "..\GameObjectSystem\OrbitBehavior.h"
#include "..\GameObjectSystem\SpinBehavior.h"

#include "..\InputSystem\Keyboard.h"

#include "..\GraphicsSystem\Camera.h"
#include "..\GraphicsSystem\CameraManager.h"

#include "..\AnimationSystem\AnimationSetRegistry.h"
#include "..\AnimationSystem\AnimationController.h"


namespace lge
{
	//
	// Static Data
	//

	GameObjectManager* GameObjectManager::singletonInstance = nullptr;



	//
	// Methods
	//

	GameObjectManager::GameObjectManager() :
		gameObjectHierarchy(),
		root(nullptr)
	{
		assert(GameObjectManager::singletonInstance == nullptr);
		GameObjectManager::singletonInstance = this;

		// Make a GameObject as root. This object will always be skipped in updates
		this->root = new GameObject("ROOT_GAME_OBJECT");

		// Establish the root of this hierarchy
		this->gameObjectHierarchy.insert(root, nullptr);
	}


	GameObjectManager::~GameObjectManager()
	{
		// Manager must exist in singleton link!
		assert(GameObjectManager::singletonInstance != nullptr);
		GameObjectManager::singletonInstance = nullptr;
	}


	// VIRTUAL
	void GameObjectManager::Load()
	{
		GameObject* gameObjSun = new GameObject(&MaterialRegistry::Find(MaterialName::Material5),
												&MeshRegistry::Find(MeshName::Sphere),	// Was Cube
												"Cube1");

		GameObject* gameObjPlanet = new GameObject(&MaterialRegistry::Find(MaterialName::Material2),
												   &MeshRegistry::Find(MeshName::Tetrahedron),
												   "Tetra1");

		GameObject* gameObjMoon = new GameObject(&MaterialRegistry::Find(MaterialName::Material4),
												 &MeshRegistry::Find(MeshName::Octahedron),
												 "Octa1");

		GameObject* gameObjSatelite = new GameObject(&MaterialRegistry::Find(MaterialName::Material3),
													 &MeshRegistry::Find(MeshName::TrianglePrism),
													 "Prism1");

		gameObjSun->GetTransform().SetPosition(Vect(0.0f, 0.0f, -24.0f));
		/*
		gameObjSun->SetCustomMovementBehavior(
			new SpinBehavior(0.9f, gameObjSun->GetTransform())
		);
		//*/

		//*
		gameObjPlanet->GetTransform().SetScale(Vect(2.7f, 2.7f, 2.7f));
		gameObjPlanet->SetCustomMovementBehavior(
			new OrbitBehavior(gameObjSun->GetTransform(),
							gameObjPlanet->GetTransform(),
							5.0f,
							1.0f
			)
		);

		gameObjMoon->GetTransform().SetScale(Vect(0.5f, 1.0f, 0.5f));
		gameObjMoon->SetCustomMovementBehavior(
			new OrbitBehavior(gameObjPlanet->GetTransform(),
					gameObjMoon->GetTransform(),
					-10.0f,
					2.0f
			)
		);

		gameObjSatelite->GetTransform().SetScale(Vect(0.9f, 0.9f, 0.9f));
		gameObjSatelite->SetCustomMovementBehavior(
			new OrbitBehavior(gameObjMoon->GetTransform(),
							gameObjSatelite->GetTransform(),
							-5.0f,
							5.0f
			)
		);
		//*/


		
		/*
		GameObjectManager::Add(gameObjPlanet, gameObjSun);
		GameObjectManager::Add(gameObjMoon, gameObjPlanet);
		GameObjectManager::Add(gameObjSatelite, gameObjMoon);
		//*/

		GameObjectManager::Add(gameObjSatelite);
		GameObjectManager::Add(gameObjMoon);
		GameObjectManager::Add(gameObjPlanet);

		GameObjectManager::Add(gameObjSun);

		GameObject* spaceFrigate = new GameObject(&MaterialRegistry::Find(MaterialName::SpaceFrigate),
												  &MeshRegistry::Find(MeshName::SpaceFrigate),
												  "SpaceFrigate1",
												  UseUnpacker,
												  "space_frigate");

		GameObject* astroboy = new GameObject(&MaterialRegistry::Find(MaterialName::Astroboy),
												  &MeshRegistry::Find(MeshName::Astroboy),
												  "Astroboy1",
												  UseUnpacker,
												  "astroboy");

		GameObject* buggy = new GameObject(&MaterialRegistry::Find(MaterialName::Buggy),
												  &MeshRegistry::Find(MeshName::Buggy),
												  "Buggy1",
												  UseUnpacker,
												  "buggy");


		GameObject* spaceFrigate2 = new GameObject(&MaterialRegistry::Find(MaterialName::Material4),
												  &MeshRegistry::Find(MeshName::SpaceFrigate),
												  "SpaceFrigate2",
												  UseUnpacker,
												  "space_frigate");

		GameObject* astroboy2 = new GameObject(&MaterialRegistry::Find(MaterialName::Material3),
											  &MeshRegistry::Find(MeshName::Astroboy),
											  "Astroboy2",
											  UseUnpacker,
											  "astroboy");


		spaceFrigate2->GetTransform().SetPosition(Vect(-25.0f, 0.0f, -16.0f));
		spaceFrigate2->GetTransform().SetScale(Vect(0.03f, 0.03f, 0.03f));


		astroboy2->GetTransform().SetPosition(Vect(20.0f, -0.5f, -24.0f));
		astroboy2->GetTransform().SetScale(Vect(0.02f, 0.025f, 0.02f));
		astroboy2->GetTransform().SetEulerAngles(Vect(-MATH_PI2, -MATH_PI2, 0.0f));


		spaceFrigate->GetTransform().SetPosition(Vect(-25.0f, 0.0f, -10.0f));
		spaceFrigate->GetTransform().SetScale(Vect(0.1f, 0.1f, 0.1f));
		spaceFrigate->GetTransform().SetEulerAngles(Vect(0.0f, MATH_PI2, 0.0f));

		astroboy->GetTransform().SetPosition(Vect(15.0f, -0.5f, -10.0f));
		astroboy->GetTransform().SetScale(Vect(0.015f, 0.015f, 0.015f));
		//astroboy->GetTransform().SetScale(Vect(0.2f, 0.2f, 0.2f));
		astroboy->GetTransform().SetEulerAngles(Vect(-MATH_PI2, 0.0f, 0.0f));

		buggy->GetTransform().SetPosition(Vect(9.0f, -1.5f, -10.0f));
		buggy->GetTransform().SetScale(Vect(0.01f, 0.01f, 0.01f));
		buggy->GetTransform().SetEulerAngles(Vect(0.0f, MATH_PI, 0.0f));


		GameObjectManager::Add(spaceFrigate);
		GameObjectManager::Add(astroboy);
		GameObjectManager::Add(buggy);

		GameObjectManager::Add(spaceFrigate2);
		GameObjectManager::Add(astroboy2);


		//*
		{
			GameObject* animatedGameObject1 = new GameObject(&MaterialRegistry::Find(MaterialName::SkinnedTextureDiffuseBear),
															 &MeshRegistry::Find(MeshName::SkinnedTeddyBear),
															 "teddy");
			animatedGameObject1->GetTransform().SetPosition(Vect(-8.0f, 0.0f, -10.0f));
			//animatedGameObject1->GetTransform().SetScale(Vect(1.0f, 1.0f, 1.0f));
			animatedGameObject1->GetTransform().SetScale(Vect(0.1f, 0.1f, 0.1f));
			animatedGameObject1->GetTransform().SetEulerAngles(Vect(0.0f, 0.0f, 0.0f));
			AnimationSet* const teddyAnim = AnimationSetRegistry::Find("teddy");
			assert(teddyAnim != nullptr);
			GameObjectManager::Add(animatedGameObject1);
			const float boneScale1 = 1.0f;
			animatedGameObject1->AddAnimation(*teddyAnim, boneScale1);
			animatedGameObject1->GetAnimationController()->SetCurrentPlayback("idle");
			animatedGameObject1->GetAnimationController()->Play();
			animatedGameObject1->GetAnimationController()->GetCurrentPlayback()->SetPlaybackSpeedScale(1.0f);
		}
		//*/


		{
			GameObject* animatedGameObject2 = new GameObject(&MaterialRegistry::Find(MaterialName::SkinnedTextureDiffueseHumanoid),
															 &MeshRegistry::Find(MeshName::SkinnedHumanoid),
															 "humanoid");
			animatedGameObject2->GetTransform().SetPosition(Vect(0.0f, 0.0f, -9.0f));
			animatedGameObject2->GetTransform().SetScale(Vect(0.071f, 0.071f, 0.071f));
			animatedGameObject2->GetTransform().SetEulerAngles(Vect(MATH_3PI4, 0.0f, 0.0f));
			AnimationSet* const humanAnim = AnimationSetRegistry::Find("humanoid");
			assert(humanAnim != nullptr);
			GameObjectManager::Add(animatedGameObject2);
			const float boneScale2 = 0.1f;
			animatedGameObject2->AddAnimation(*humanAnim, boneScale2);
			animatedGameObject2->GetAnimationController()->SetCurrentPlayback("punch");
			animatedGameObject2->GetAnimationController()->Play();
		}

		{
			GameObject* animatedGameObject1 = new GameObject(&MaterialRegistry::Find(MaterialName::SkinnedTextureDiffuseBear),
															 &MeshRegistry::Find(MeshName::SkinnedTeddyBear),
															 "teddy2");
			animatedGameObject1->GetTransform().SetPosition(Vect(-6.0f, 0.0f, -10.0f));
			//animatedGameObject1->GetTransform().SetScale(Vect(1.0f, 1.0f, 1.0f));
			animatedGameObject1->GetTransform().SetScale(Vect(0.1f, 0.1f, 0.1f));
			animatedGameObject1->GetTransform().SetEulerAngles(Vect(0.0f, 0.0f, 0.0f));
			AnimationSet* const teddyAnim = AnimationSetRegistry::Find("teddy");
			assert(teddyAnim != nullptr);
			GameObjectManager::Add(animatedGameObject1);
			const float boneScale1 = 1.0f;
			animatedGameObject1->AddAnimation(*teddyAnim, boneScale1);
			animatedGameObject1->GetAnimationController()->SetCurrentPlayback("idle_compressed");
			animatedGameObject1->GetAnimationController()->Play();
			animatedGameObject1->GetAnimationController()->GetCurrentPlayback()->SetPlaybackSpeedScale(1.0f);
		}

		{
			GameObject* animatedGameObject2 = new GameObject(&MaterialRegistry::Find(MaterialName::SkinnedTextureDiffueseHumanoid),
															 &MeshRegistry::Find(MeshName::SkinnedHumanoid),
															 "humanoid2");
			animatedGameObject2->GetTransform().SetPosition(Vect(4.0f, 0.0f, -9.0f));
			animatedGameObject2->GetTransform().SetScale(Vect(0.071f, 0.071f, 0.071f));
			animatedGameObject2->GetTransform().SetEulerAngles(Vect(MATH_3PI4, 0.0f, 0.0f));
			AnimationSet* const humanAnim = AnimationSetRegistry::Find("humanoid");
			assert(humanAnim != nullptr);
			GameObjectManager::Add(animatedGameObject2);
			const float boneScale2 = 0.1f;
			animatedGameObject2->AddAnimation(*humanAnim, boneScale2);
			animatedGameObject2->GetAnimationController()->SetCurrentPlayback("punch_compressed");
			animatedGameObject2->GetAnimationController()->Play();
		}
	}


	// VIRTUAL
	void GameObjectManager::Unload()
	{
		this->gameObjectHierarchy.remove(this->root);
		this->root = nullptr;
		assert(this->gameObjectHierarchy.getNumberOfNodes() == 0);
	}




	// VIRTUAL
	void GameObjectManager::Update()
	{
		PCSTreeForwardIterator itr(this->gameObjectHierarchy);
		GameObject* currObject = (GameObject*)itr.First();	// Root always bypassed
		bool shouldUpdateSphereRenderStatus = false;
		static bool shouldDrawSpheres = false;

		// Toggle rendering of bounding spheres
		if (Input::Keyboard::GetKeyDown(Input::Key::B))
		{
			shouldUpdateSphereRenderStatus = true;
			shouldDrawSpheres = !shouldDrawSpheres;
		}

		while (!itr.IsDone())
		{
			currObject->Update();
			if (shouldUpdateSphereRenderStatus)
			{
				currObject->SetRenderBoundingSphere(shouldDrawSpheres);
			}

			Camera& activeCamera = Camera::GetActiveCamera();
			//Camera& activeCamera = CameraManager::Find(1);  // For occlusion culling demo
			currObject->SetIfWillRender( activeCamera.IsGameObjectInFrustum(currObject) );

			// Next GameObject
			currObject = (GameObject*)itr.Next();
		}
	}


	void GameObjectManager::Draw() const
	{
		PCSTreeForwardIterator itr(this->gameObjectHierarchy);
		GameObject* currObject = (GameObject*)itr.First();	// Root always bypassed

		while (!itr.IsDone())
		{
			currObject->Draw();

			currObject = (GameObject*)itr.Next();
		}
	}




	// STATIC
	// Must be dynamically allocated, for it will be deleted by this manager later
	void GameObjectManager::Add(GameObject* newGameObject, GameObject* const parent)
	{
		assert(newGameObject != nullptr);
		assert(newGameObject != parent);

		GameObjectManager* const inst = GameObjectManager::singletonInstance;

		// If parent wasn't provided, add to root
		if (parent == nullptr)
		{
			inst->gameObjectHierarchy.insert(newGameObject, inst->root);
		}
		// Otherwise, add to parent
		else
		{
			inst->gameObjectHierarchy.insert(newGameObject, parent);
		}
	}


	// STATIC
	// Find any GameObject by name
	GameObject* const GameObjectManager::Find(const char* const name)
	{
		PCSTreeForwardIterator itr(GameObjectManager::singletonInstance->gameObjectHierarchy);
		GameObject* foundObject = (GameObject*) itr.First();	// Root always bypassed

		while (!itr.IsDone())
		{
			if (foundObject->GetName() == name)
			{
				// Found!
				break;
			}

			foundObject = (GameObject*) itr.Next();
		}

		return foundObject;
	}
}