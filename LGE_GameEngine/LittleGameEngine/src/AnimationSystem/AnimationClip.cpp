#include "AnimationClip.h"
#include <cassert>
#include <utility>

namespace lge
{
	static const TimeUnit ZERO_TIME(DurationBasis::Zero);



	// Ctor with mutable clip data loaded separately
	AnimationClip::AnimationClip(AnimationClipSetter* const newClipData) :
		maxTime(),
		numOfKeyframes(0u),
		keyframes(nullptr),
		name(),
		setId(0xFBFBFBFB),
		doesLoop(false)
	{
		this->maxTime = newClipData->GetMaxTime();
		this->numOfKeyframes = newClipData->GetNumberOfKeyframes();
		this->keyframes = newClipData->GetKeyframeArrayOnce();
		this->name = newClipData->GetNameOnce();
		this->setId = newClipData->GetId();
		this->doesLoop = newClipData->DoesLoop();

		assert(this->keyframes != nullptr);
		assert(this->name != nullptr);
		assert(this->numOfKeyframes > 0);
	}

	// Dtor
	AnimationClip::~AnimationClip()
	{
		delete[] keyframes;
	}





	// Get the full length of playback for this clip
	const TimeUnit AnimationClip::GetMaxTime() const
	{
		return this->maxTime;
	}

	// Get the number of keyframes in this clip
	const unsigned int AnimationClip::GetNumberOfKeyframes() const
	{
		return this->numOfKeyframes;
	}

	// Get the information for a keyframe given its index
	const KeyFrame& AnimationClip::GetKeyframeAt(const unsigned int index) const
	{
		assert(index < this->numOfKeyframes);
		return this->keyframes[index];
	}

	// Get the name of this clip
	const char* const AnimationClip::GetName() const
	{
		return this->name.GetString();
	}

	// Get the ID of this clip (unique per AnimationSet)
	const unsigned int AnimationClip::GetId() const
	{
		return this->setId;
	}

	// Get the number of joints in the clips (should be the same across clips)
	const unsigned int AnimationClip::GetNumberOfJoints() const
	{
		return this->keyframes[0].GetNumberOfJoints();
	}

	// Was this clip meant to loop by default?
	const bool AnimationClip::DoesLoop() const
	{
		return this->doesLoop;
	}

}