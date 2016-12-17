#ifndef H_LGE_ANIMATION_PLAYBACK
#define H_LGE_ANIMATION_PLAYBACK
#include "KeyFrame.h"
#include "..\TimeSystem\TimeUnit.h"
#include "..\AbstractDataTypes\CString.h"

namespace lge
{
	// Forward declare
	class GpuProgram;

	// Abstract class that defines how to play an animation (whether clips or a mix of clips)
	class AnimationPlayback
	{
	public:
		
		//
		// Ctor + Dtor
		//
		
		AnimationPlayback(const unsigned int numOfJoints, const TimeUnit maxPlayTime, const bool loops, const char* const playbackName, const unsigned int nameHash);
		virtual ~AnimationPlayback();


		//
		// Methods
		//

		void Play();
		void Stop();
		void Pause();

		// This should only ever be called once per frame in an update loop
		void Update(const TimeUnit deltaTime, GpuProgram* const frameMixerProg);



		//
		// Accessors
		//

		const KeyFrame& GetCurrentFrame() const;

		const bool IsPlaying() const;

		const TimeUnit GetCurrentPlayTime() const;

		const CString& GetPlaybackName() const;

		const float GetPlaybackSpeedScale() const;
		void SetPlaybackSpeedScale(const float newScale);

		const bool IsLooping() const;
		void SetLoop(const bool loops);

		const unsigned int GetNumberOfJoints() const;

		const unsigned int GetPlaybackNameHash() const;

		const KeyFrame* const GetToFrame() const;

		const KeyFrame* const GetFromFrame() const;


		//
		// Only for Playbacks
		//

		void SetTime(const TimeUnit& newTime);

		// Determine how the from-frame and to-frame are defined
		virtual void DetermineFromAndToFrames() = 0;

	protected:

		//
		// Data
		//

		TimeUnit currentPlayTime;
		TimeUnit maxPlayDuration;
		KeyFrame* frameMix;
		const KeyFrame* frameFrom;
		const KeyFrame* frameTo;
		CString name;
		float playbackSpeedScale;
		unsigned int nameHash;
		bool isPlaying;
		bool isLooping;

		

	private:



		//
		// Deleted Methods
		//

		AnimationPlayback() = delete;
		AnimationPlayback(const AnimationPlayback& other) = delete;
		AnimationPlayback& operator=(const AnimationPlayback& other) = delete;

		void AdvanceTime(const TimeUnit& deltaTime);
	};
}
#endif