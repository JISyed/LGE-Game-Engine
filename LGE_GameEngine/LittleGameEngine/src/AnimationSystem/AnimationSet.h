#ifndef H_LGE_ANIMATION_SET
#define H_LGE_ANIMATION_SET
#include "AnimationClip.h"
#include "AnimationClipList.h"
#include "AnimationSkeleton.h"

namespace lge
{
	class AnimationSet
	{
	public:
		
		//
		// Ctor + Dtor
		//
		
		//AnimationSet(AnimationSkeleton* const newSkeleton);
		AnimationSet();
		~AnimationSet();



		//
		// Methods
		//

		// Add a new clip to this set
		void AddClip(AnimationClip* const newClip);

		// Set a skeleton to this animation set (only once)
		void AddSkeletonOnce(AnimationSkeleton* const newSkeleton);

		// Get the iterator for the clip list
		AnimationClipList::Iterator GetClipIterator() const;

		// Get a clip by its integer ID
		const AnimationClip* const GetClipById(const unsigned int id) const;

		// Get a clip by its name
		const AnimationClip* const GetClipByName(const char* const name) const;

		// Get number of clips in this set
		const unsigned int GetNumberOfClips() const;

		// Get the skeleton data of this set
		const AnimationSkeleton* const GetSkeleton() const;

		// Based off skeleton name
		const CString& GetSetName() const;

		// Based off skeleton hash
		const unsigned int GetSetHashId() const;

		// For GenericList
		const unsigned int GetId() const;


	private:

		//
		// Data
		//

		AnimationClipList animationClips;	// All animation clips that are a part of this set
		AnimationSkeleton* skeleton;		// The skeleton that is animated only by this set's clips



		//
		// Deleted Methods
		//

		//AnimationSet() = delete;
		AnimationSet(const AnimationSet& other) = delete;
		AnimationSet& operator=(const AnimationSet& other) = delete;

	};
}
#endif