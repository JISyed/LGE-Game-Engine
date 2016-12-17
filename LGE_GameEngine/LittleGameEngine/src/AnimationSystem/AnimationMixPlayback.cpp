#include "AnimationMixPlayback.h"
#include "..\AbstractDataTypes\CString.h"
#include <cassert>
#include <string>

namespace lge
{
	AnimationMixPlayback::AnimationMixPlayback(AnimationPlayback* const leftPlayback, AnimationPlayback* const rightPlayback, const float mixTime, const bool doesLoop) :
		AnimationPlayback(leftPlayback->GetNumberOfJoints(), 
						  mixTime * TimeUnit(DurationBasis::OneSecond), 
						  doesLoop, 
						  (std::string(leftPlayback->GetPlaybackName().GetString()) + std::string("-mix-") + std::string(rightPlayback->GetPlaybackName().GetString())).c_str(), 
						  leftPlayback->GetPlaybackNameHash() ^ rightPlayback->GetPlaybackNameHash()
						  ),
		left(leftPlayback),
		right(rightPlayback)
	{
		assert(leftPlayback != nullptr);
		assert(rightPlayback != nullptr);
		assert(leftPlayback->GetNumberOfJoints() == rightPlayback->GetNumberOfJoints());
	}

	// VIRTUAL
	AnimationMixPlayback::~AnimationMixPlayback()
	{
	}




	const AnimationPlayback* const AnimationMixPlayback::GetLeftPlayback() const
	{
		return this->left;
	}

	const AnimationPlayback* const AnimationMixPlayback::GetRightPlayback() const
	{
		return this->right;
	}

	void AnimationMixPlayback::SetLeftPlayback(AnimationPlayback* const newPlayback)
	{
		assert(this->left->GetNumberOfJoints() == newPlayback->GetNumberOfJoints());

		this->left = newPlayback;
	}

	void AnimationMixPlayback::SetRightPlayback(AnimationPlayback* const newPlayback)
	{
		assert(this->right->GetNumberOfJoints() == newPlayback->GetNumberOfJoints());

		this->right = newPlayback;
	}


	// VIRTUAL OVERRIDE
	// Determine how the from-frame and to-frame are defined
	void AnimationMixPlayback::DetermineFromAndToFrames()
	{
		this->left->Play();
		this->right->Play();

		this->left->SetTime(this->currentPlayTime);
		this->right->SetTime(this->currentPlayTime);

		this->left->DetermineFromAndToFrames();
		this->right->DetermineFromAndToFrames();

		this->frameFrom = &(this->left->GetCurrentFrame());
		this->frameTo = &(this->right->GetCurrentFrame());
	}
}