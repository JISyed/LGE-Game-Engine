#include "AnimationSet.h"
#include <cassert>

namespace lge
{
	AnimationSet::AnimationSet(/*AnimationSkeleton* const newSkeleton*/) :
		animationClips(),
		skeleton(nullptr)
	{
		//assert(newSkeleton != nullptr);
	}

	AnimationSet::~AnimationSet()
	{
		if (this->skeleton != nullptr)
		{
			delete this->skeleton;
		}
	}




	// Add a new clip to this set
	void AnimationSet::AddClip(AnimationClip* const newClip)
	{
		assert(newClip != nullptr);

		this->animationClips.AddToBack(newClip);
	}

	// Set a skeleton to this animation set (only once)
	void AnimationSet::AddSkeletonOnce(AnimationSkeleton* const newSkeleton)
	{
		assert(newSkeleton != nullptr);
		assert(this->skeleton == nullptr);
		
		this->skeleton = newSkeleton;
	}


	// Get the iterator for the clip list
	AnimationClipList::Iterator AnimationSet::GetClipIterator() const
	{
		return this->animationClips.GetIterator();
	}

	// Get a clip by its integer ID
	const AnimationClip* const AnimationSet::GetClipById(const unsigned int id) const
	{
		return this->animationClips.FindClipById(id);
	}

	// Get a clip by its name
	const AnimationClip* const AnimationSet::GetClipByName(const char* const name) const
	{
		assert(name != nullptr);

		return this->animationClips.FindClipByName(name);
	}

	// Get number of clips in this set
	const unsigned int AnimationSet::GetNumberOfClips() const
	{
		return this->animationClips.GetNumberOfClips();
	}

	// Get the skeleton data of this set
	const AnimationSkeleton* const AnimationSet::GetSkeleton() const
	{
		return this->skeleton;
	}

	// Based off skeleton name
	const CString& AnimationSet::GetSetName() const
	{
		return this->skeleton->GetName();
	}

	// Based off skeleton hash
	const unsigned int AnimationSet::GetSetHashId() const
	{
		return this->skeleton->GetHashId();
	}

	// For GenericList
	const unsigned int AnimationSet::GetId() const
	{
		return this->GetSetHashId();
	}

}