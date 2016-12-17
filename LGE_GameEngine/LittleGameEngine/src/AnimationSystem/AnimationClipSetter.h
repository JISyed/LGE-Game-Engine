#ifndef H_LGE_ANIMATION_CLIP_SETTER
#define H_LGE_ANIMATION_CLIP_SETTER
#include "KeyFrame.h"
#include "..\TimeSystem\TimeUnit.h"
#include "..\AbstractDataTypes\CString.h"

namespace lge
{
	// A data class whose sole purpose is to setup the data of an Animation Clip
	class AnimationClipSetter
	{
	public:
		
		//
		// Ctor / Dtor
		//
		
		AnimationClipSetter();
		~AnimationClipSetter();


		//
		// Setters
		//

		// Set the full duration of this clip
		void SetMaxTime(const TimeUnit fullDuration);

		// Set the keyframe data. Keyframes must already be dynamically allocated into an array
		void SetKeyframes(const unsigned int numberOfKeyframes, KeyFrame* const keyFrameArray);

		// Set the name of this clip
		void SetName(CString&& newName);

		// Set the ID of this clip (which is unique to its AnimationSet)
		void SetId(const unsigned int newId);

		// Set if this clip was meant to loop when read by a playback
		void SetLooping(const bool loops);


		//
		// Getters (Only Call Once)
		//

		// Get the full duration of this clip (can be called many times)
		const TimeUnit GetMaxTime() const;

		// Get the number of keyframes (can be called many times)
		const unsigned int GetNumberOfKeyframes() const;
		
		// Get the keyframe array. Only call once!
		KeyFrame* const GetKeyframeArrayOnce();
		
		// Get the name of this clip. Only call once!
		CString&& GetNameOnce();

		// Get the ID of this clip (which is unique to its AnimationSet)
		const unsigned int GetId() const;

		// Was this clip meant to loop?
		const bool DoesLoop() const;


	private:

		//
		// Data
		//

		TimeUnit maxTime;				// The current time position of this clip
		unsigned int numOfKeyframes;	// The number of keyframes
		KeyFrame* keyframes;			// All keyframes of this clip
		CString name;					// The name of this clip
		unsigned int setId;				// The id of this clip (unique to the AnimationSet)
		bool doesLoop;					// Indicates if this clip was meant to loop


		//
		// Deleted Methods
		//

		// No copy
		AnimationClipSetter(const AnimationClipSetter& other) = delete;

		// No copy
		AnimationClipSetter& operator=(const AnimationClipSetter& other) = delete;

	};	
}
#endif