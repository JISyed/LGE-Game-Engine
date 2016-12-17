#ifndef H_LGE_ANIMATION_PLAYBACK_MIX
#define H_LGE_ANIMATION_PLAYBACK_MIX
#include "AnimationPlayback.h"

namespace lge
{
	class AnimationMixPlayback final : public AnimationPlayback
	{
	public:
		AnimationMixPlayback(AnimationPlayback* const leftPlayback, AnimationPlayback* const rightPlayback, const float mixTimeInSec, const bool doesLoop);
		virtual ~AnimationMixPlayback();


		const AnimationPlayback* const GetLeftPlayback() const;
		const AnimationPlayback* const GetRightPlayback() const;
		void SetLeftPlayback(AnimationPlayback* const newPlayback);
		void SetRightPlayback(AnimationPlayback* const newPlayback);


	protected:

		// Determine how the from-frame and to-frame are defined
		virtual void DetermineFromAndToFrames() override;

	private:

		//
		// Data
		//

		AnimationPlayback* left;
		AnimationPlayback* right;



		// 
		// Deleted Methods
		//

		AnimationMixPlayback() = delete;
		AnimationMixPlayback(const AnimationMixPlayback& other) = delete;
		AnimationMixPlayback& operator=(const AnimationMixPlayback& other) = delete;


	};
}
#endif