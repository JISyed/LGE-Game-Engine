#ifndef H_LGE_ANIMATION_CONTROLLER
#define H_LGE_ANIMATION_CONTROLLER
#include "AnimationPlaybackList.h"
#include "AnimationPlayback.h"
#include "AnimationClipPlayback.h"
#include "AnimationSet.h"
#include "..\TimeSystem\TimeUnit.h"
#include "Matrix.h"
#include "..\GraphicsSystem\GpuBuffer.h"

namespace lge
{
	class MeshRenderer;

	class AnimationController
	{
	public:

		//
		// Ctor + Dtor
		//

		AnimationController(const AnimationSet& animationData);
		~AnimationController();

		void Play();
		void Pause();
		void Stop();

		void Update(const TimeUnit deltaTime);

		void CalculateWorldBoneMats(MeshRenderer* renderer);

		const KeyFrame& GetFinalMix() const;

		void SetCurrentPlayback(const char* const playbackName);
		void SetCurrentPlayback(const unsigned int playbackHash);

		AnimationPlayback* const GetCurrentPlayback() const;

		const AnimationSet& GetAnimationSet() const;

		GpuBuffer* const GetGlobalMatricesGpuBuffer() const;


	private:

		//
		// Internal Enum
		//

		enum class PlayState
		{
			Playing,
			Paused,
			Stopped
		};



		//
		// Data
		//

		AnimationPlayback* currentPlayback;
		KeyFrame* finalMix;
		GpuBuffer* localMatricesBuffer;		// Joint matrices in local space
		GpuBuffer* globalMatricesBuffer;	// Joint matrices in world space
		AnimationPlaybackList playbacks;
		const AnimationSet& animationSet;
		PlayState playState;
		Matrix* finalMixWorldMats;		// Final mix as world matrices


		//
		// Private Methods
		//

		void SetCurrentPlaybackCommon(AnimationPlayback* const newPlayback);



		//
		// Deleted Methods
		//

		AnimationController() = delete;
		AnimationController(const AnimationController& other) = delete;
		AnimationController& operator=(const AnimationController& other) = delete;
	};

	
}
#endif