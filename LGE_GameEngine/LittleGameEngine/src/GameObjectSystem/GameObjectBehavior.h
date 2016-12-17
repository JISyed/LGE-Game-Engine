#ifndef GAME_OBJECT_BEHAVIOR_H
#define GAME_OBJECT_BEHAVIOR_H

namespace lge
{
	// Based of the component game design pattern.
	// Allows unique behaviors to GameObjects
	class GameObjectBehavior
	{
	public:

		//
		// Ctor / Dtor
		//

		GameObjectBehavior();
		virtual ~GameObjectBehavior();




		//
		// Lifetime Methods
		//

		virtual void Update() = 0;



	private:

	};
}

#endif