#include "AnimationClipPlayback.h"
#include "..\AbstractDataTypes\CString.h"
#include <cassert>

namespace lge
{
	AnimationClipPlayback::AnimationClipPlayback(AnimationClip* const newClip) :
		AnimationPlayback(newClip->GetNumberOfJoints(), newClip->GetMaxTime(), newClip->DoesLoop(), newClip->GetName(), newClip->GetId()),
		clip(newClip)
	{
		assert(newClip != nullptr);
	}

	// VIRTUAL
	AnimationClipPlayback::~AnimationClipPlayback()
	{
	}




	const AnimationClip* const AnimationClipPlayback::GetClip() const
	{
		return this->clip;
	}

	void AnimationClipPlayback::SetAnimationClip(AnimationClip* const newClip)
	{
		assert(this->clip->GetNumberOfJoints() == newClip->GetNumberOfJoints());

		this->clip = newClip;
	}


	// VIRTUAL OVERRIDE
	// Determine how the from-frame and to-frame are defined
	void AnimationClipPlayback::DetermineFromAndToFrames()
	{
		unsigned int fromIndex = 0;
		unsigned int toIndex = 1;

		for (unsigned int i = 1u; i < this->clip->GetNumberOfKeyframes(); i++)
		{
			toIndex = i;
			fromIndex = i - 1;

			if (this->clip->GetKeyframeAt(toIndex).GetKeyframeTime() >= this->currentPlayTime)
			{
				break;
			}
		}

		this->frameFrom = &(this->clip->GetKeyframeAt(fromIndex));
		this->frameTo = &(this->clip->GetKeyframeAt(toIndex));
	}


}