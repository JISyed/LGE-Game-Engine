#include "AnimationSetRegistry.h"
#include <cassert>
#include "..\AbstractDataTypes\CString.h"
#include "..\UnpackagerSystem\ResourceUnpacker.h"

namespace lge
{
	//
	// Static Data
	//

	AnimationSetRegistry* AnimationSetRegistry::singletonInstance = nullptr;



	//
	// Methods
	//

	AnimationSetRegistry::AnimationSetRegistry() :
		animationSetList()
	{
		assert(AnimationSetRegistry::singletonInstance == nullptr);
		AnimationSetRegistry::singletonInstance = this;
	}

	// VIRTUAL
	AnimationSetRegistry::~AnimationSetRegistry()
	{
		// List must be emptied before destroying manager!
		assert(this->animationSetList.GetNumberOfElements() == 0);

		// Manager must exist in singleton link!
		assert(AnimationSetRegistry::singletonInstance != nullptr);
		AnimationSetRegistry::singletonInstance = this;
	}





	// VIRTUAL
	void AnimationSetRegistry::Load()
	{
		AnimationSetRegistry::Create(UseUnpacker, "teddy_tga");
		AnimationSetRegistry::Create(UseUnpacker, "humanoid");
	}


	// VIRTUAL
	void AnimationSetRegistry::Unload()
	{
		while (this->animationSetList.GetNumberOfElements() != 0)
		{
			AnimationSet* oldObject = this->animationSetList.RemoveFront();
			delete oldObject;
		}
	}


	// VIRTUAL
	void AnimationSetRegistry::Update()
	{
		// Intentionally does nothing
	}






	// STATIC
	// Must be dynamically allocated, for it will be deleted by this manager later
	void AnimationSetRegistry::Add(AnimationSet* const newObject)
	{
		assert(newObject != nullptr);
		AnimationSetRegistry::singletonInstance->animationSetList.AddFront(newObject);
	}

	// STATIC
	// Find any AnimationSet
	AnimationSet* const AnimationSetRegistry::Find(const unsigned int hashOfName)
	{
		return AnimationSetRegistry::singletonInstance->animationSetList.FindById( static_cast<unsigned int>(hashOfName) );
	}

	// STATIC
	// Find any AnimationSet
	AnimationSet * const AnimationSetRegistry::Find(const char* const name)
	{
		static AnimationSetRegistry* const inst = AnimationSetRegistry::singletonInstance;

		AnimationSet* result = nullptr;

		{
			auto itr = inst->animationSetList.GetIterator();
			AnimationSet* curr = nullptr;
			while (itr.IsDone() == false)
			{
				curr = itr.CurrentItem();

				if (curr->GetSetName() == name)
				{
					// Found it
					result = curr;
					break;
				}

				itr.Next();
			}
		}

		return result;
	}



	// STATIC
	// Factory for AnimationSets. Automatically added
	AnimationSet* const AnimationSetRegistry::Create(const UseUnpacker_t use, const char* const name)
	{
		use;
		assert(AnimationSetRegistry::singletonInstance != nullptr);

		AnimationSet* newAnimation = new AnimationSet();
		bool success = ResourceUnpacker::ReadAnimationSet(name, newAnimation);
		assert(success); success;

		if (newAnimation != nullptr)
		{
			AnimationSetRegistry::Add(newAnimation);
		}

		return newAnimation;
	}
}