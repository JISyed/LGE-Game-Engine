#ifndef LGE_ANIMATION_SET_MANAGER_H
#define LGE_ANIMATION_SET_MANAGER_H

#include "..\EngineFoundation\ResourseRegistry.h"
#include "..\AbstractDataTypes\GenericList.h"
#include "..\UnpackagerSystem\enumUseUnpackerType.h"
#include "AnimationSet.h"

namespace lge
{
	// Serves as a container for holding all the loaded AnimationSets in the game
	class AnimationSetRegistry final : public ResourceRegistry
	{
	public:

		//
		// Ctor / Dtor
		//

		AnimationSetRegistry();
		virtual ~AnimationSetRegistry();



		//
		// Contracts
		//

		virtual void Load() override;
		virtual void Unload() override;
		virtual void Update() override;



		//
		// Static Methods
		//

		// Find any AnimationSet
		static AnimationSet* const Find(const unsigned int hashOfName);
		static AnimationSet* const Find(const char* const name);

		// Factory for AnimationSet. Automatically added
		static AnimationSet* const Create(const UseUnpacker_t use, const char* const name);




	private:

		//
		// Data
		//

		GenericList<AnimationSet> animationSetList;



		//
		// Static Data
		//

		static AnimationSetRegistry* singletonInstance;



		//
		// Private Routines
		//

		// Must be dynamically allocated, for it will be deleted by this manager later
		static void Add(AnimationSet* const newObject);



		//
		// Deleted Methods
		//

		// No copy ctor
		AnimationSetRegistry(const AnimationSetRegistry& other) = delete;

		// No copy assignment
		AnimationSetRegistry& operator=(const AnimationSetRegistry& other) = delete;

		// No move ctor
		AnimationSetRegistry(AnimationSetRegistry&& other) = delete;

		// No move assignment
		AnimationSetRegistry& operator=(AnimationSetRegistry&& other) = delete;
	};
}
#endif