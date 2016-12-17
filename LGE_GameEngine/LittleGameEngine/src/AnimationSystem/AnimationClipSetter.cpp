#include "AnimationClipSetter.h"
#include <cassert>
#include <cstring>
#include <utility>

namespace lge
{
	AnimationClipSetter::AnimationClipSetter() :
		numOfKeyframes(0u),
		keyframes(nullptr),
		name(),
		doesLoop(false)
	{
	}

	AnimationClipSetter::~AnimationClipSetter()
	{
		if (this->keyframes != nullptr)
		{
			delete[] this->keyframes;
		}
	}


	// Set the full duration of this clip
	void AnimationClipSetter::SetMaxTime(const TimeUnit fullDuration)
	{
		this->maxTime = fullDuration;
	}

	// Set the keyframe data. Keyframes must already be dynamically allocated into an array
	void AnimationClipSetter::SetKeyframes(const unsigned int numberOfKeyframes, KeyFrame* const keyFrameArray)
	{
		this->numOfKeyframes = numberOfKeyframes;
		this->keyframes = keyFrameArray;
	}

	// Set the name of this clip
	void AnimationClipSetter::SetName(CString&& newName)
	{
		// Name must not exist yet
		assert(this->name.IsNull());

		this->name = std::move(newName);
	}

	// Set the ID of this clip (which is unique to its AnimationSet)
	void AnimationClipSetter::SetId(const unsigned int newId)
	{
		this->setId = newId;
	}

	// Set if this clip was meant to loop when read by a playback
	void AnimationClipSetter::SetLooping(const bool loops)
	{
		this->doesLoop = loops;
	}



	// Get the full duration of this clip (can be called many times)
	const TimeUnit AnimationClipSetter::GetMaxTime() const
	{
		return this->maxTime;
	}

	// Get the number of keyframes (can be called many times)
	const unsigned int AnimationClipSetter::GetNumberOfKeyframes() const
	{
		return this->numOfKeyframes;
	}

	// Get the keyframe array. Only call once!
	KeyFrame* const AnimationClipSetter::GetKeyframeArrayOnce()
	{
		// Don't call multiple times!
		assert(this->keyframes != nullptr);

		KeyFrame* const data = this->keyframes;
		this->keyframes = nullptr;	// Invalidate
		return data;
	}

	// Get the name of this clip. Only call once!
	CString&& AnimationClipSetter::GetNameOnce()
	{
		// Don't call multiple times!
		assert(this->name.IsNull() == false);

		return std::move(this->name);
	}

	// Get the ID of this clip (which is unique to its AnimationSet)
	const unsigned int AnimationClipSetter::GetId() const
	{
		return this->setId;
	}

	// Was this clip meant to loop?
	const bool AnimationClipSetter::DoesLoop() const
	{
		return this->doesLoop;
	}


}