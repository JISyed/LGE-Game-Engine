#ifndef H_LGE_ANIMATION_PLAYBACK_CLIP
#define H_LGE_ANIMATION_PLAYBACK_CLIP
#include "AnimationPlayback.h"
#include "AnimationClip.h"

namespace lge
{
	class AnimationClipPlayback final : public AnimationPlayback
	{
	public:
		AnimationClipPlayback(AnimationClip* const newClip);
		virtual ~AnimationClipPlayback();


		const AnimationClip* const GetClip() const;
		void SetAnimationClip(AnimationClip* const newClip);


	protected:

		// Determine how the from-frame and to-frame are defined
		virtual void DetermineFromAndToFrames() override;

	private:

		//
		// Data
		//

		AnimationClip* clip;



		// 
		// Deleted Methods
		//

		AnimationClipPlayback() = delete;
		AnimationClipPlayback(const AnimationClipPlayback& other) = delete;
		AnimationClipPlayback& operator=(const AnimationClipPlayback& other) = delete;


	};
}
#endif