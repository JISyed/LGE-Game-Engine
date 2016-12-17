#ifndef H_LGE_ANIMATION_CLIP
#define H_LGE_ANIMATION_CLIP
#include "AnimationClipSetter.h"
#include "..\AbstractDataTypes\CString.h"

namespace lge
{
	// A collection of keyframes that make up one playable animation
	class AnimationClip
	{
	public:

		//
		// Ctor / Dtor
		//
		
		// Ctor with mutable clip data loaded separately
		AnimationClip(AnimationClipSetter* const newClipData);
		
		// Dtor
		~AnimationClip();




		//
		// Getters
		//

		// Get the full length of playback for this clip
		const TimeUnit GetMaxTime() const;

		// Get the number of keyframes in this clip
		const unsigned int GetNumberOfKeyframes() const;

		// Get the information for a keyframe given its index
		const KeyFrame& GetKeyframeAt(const unsigned int index) const;

		// Get the name of this clip
		const char* const GetName() const;

		// Get the ID of this clip (unique per AnimationSet)
		const unsigned int GetId() const;

		// Get the number of joints in the clips (should be the same across clips)
		const unsigned int GetNumberOfJoints() const;

		// Was this clip meant to loop by default?
		const bool DoesLoop() const;


	private:

		//
		// Data
		//

		TimeUnit maxTime;				// Full duration of this clip
		unsigned int numOfKeyframes;	// The number of keyframes
		KeyFrame* keyframes;			// All keyframes of this clip
		CString name;					// The name of this clip
		unsigned int setId;				// Clip ID for reference from AnimationSet
		bool doesLoop;					// Indicates if this clip was meant to loop
		

		//
		// Deleted Methods
		//

		// No default ctor
		AnimationClip() = delete;

		// No copy
		AnimationClip(const AnimationClip& other) = delete;

		// No copy
		AnimationClip& operator=(const AnimationClip& other) = delete;

	};
}
#endif