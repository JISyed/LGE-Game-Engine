#ifndef LGE_GAMEOBJECT_MANAGER_H
#define LGE_GAMEOBJECT_MANAGER_H

#include "..\EngineFoundation\ResourseRegistry.h"
#include "..\PCS\PCSTree.h"
#include "GameObject.h"	// Cannot forward declare until GameObjectName is removed

namespace lge
{
	// Regulates every GameObject that currently exists in the game
	class GameObjectManager final : public ResourceRegistry
	{
	public:

		//
		// Ctor / Dtor
		//

		GameObjectManager();
		virtual ~GameObjectManager();


		//
		// Contracts
		//

		virtual void Load() override;
		virtual void Unload() override;
		virtual void Update() override;


		//
		// Methods
		//

		// Draw every GameObject that currently exists
		void Draw() const;


		//
		// Static Methods
		//

		// Must be dynamically allocated, for it will be deleted by this manager later.
		// If the parent is nullptr, then the new object will be added under the root
		static void Add(GameObject* newGameObject, GameObject* const parent = nullptr);

		// Find any GameObject by name
		static GameObject* const Find(const char* const name);
		

	private:

		//
		// Data
		//

		PCSTree gameObjectHierarchy;
		GameObject* root;


		//
		// Static Data
		//

		static GameObjectManager* singletonInstance;




		//
		// Deleted Methods
		//

		// No copy ctor
		GameObjectManager(const GameObjectManager& other) = delete;

		// No copy assignment
		GameObjectManager& operator=(const GameObjectManager& other) = delete;

		// No move ctor
		GameObjectManager(GameObjectManager&& other) = delete;

		// No move assignment
		GameObjectManager& operator=(GameObjectManager&& other) = delete;
	};
}
#endif