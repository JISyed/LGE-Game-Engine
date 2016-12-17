#include "AnimationPlayback.h"
#include <cassert>
#include "..\EngineUtilities\Time.h"
#include "MathApp.h"
#include "..\GraphicsSystem\GpuProgram.h"
#include "..\GraphicsSystem\GpuBuffer.h"
#include "..\GraphicsSystem\GpuBufferVao.h"


namespace lge
{

	static const TimeUnit ZERO_TIME = TimeUnit(DurationBasis::Zero);


	AnimationPlayback::AnimationPlayback(const unsigned int numOfJoints, const TimeUnit maxPlayTime, const bool loops, const char* const playbackName, const unsigned int playbackNameHash) :
		currentPlayTime(DurationBasis::Zero),
		maxPlayDuration(maxPlayTime),
		frameMix(new KeyFrame(TimeUnit(), new AnimationJoint[numOfJoints], numOfJoints)),
		frameFrom(nullptr),
		frameTo(nullptr),
		name(playbackName),
		playbackSpeedScale(1.0f),
		nameHash(playbackNameHash),
		isPlaying(false),
		isLooping(loops)
	{
		assert(numOfJoints != 0);
	}


	// VIRTUAL
	AnimationPlayback::~AnimationPlayback()
	{
		assert(this->frameMix != nullptr);
		delete this->frameMix;
		this->frameFrom = nullptr;
		this->frameTo = nullptr;
	}



	void AnimationPlayback::Play()
	{
		this->isPlaying = true;
	}

	void AnimationPlayback::Stop()
	{
		this->isPlaying = false;
		this->currentPlayTime = ZERO_TIME;
	}

	void AnimationPlayback::Pause()
	{
		this->isPlaying = false;
	}


	// This should only ever be called once per frame in an update loop
	void AnimationPlayback::Update(const TimeUnit deltaTime, GpuProgram* const frameMixerProg)
	{
		if (this->isPlaying)
		{
			// Advance time
			this->AdvanceTime(deltaTime);

			// Determine if non-looping animation ends
			if (!this->isLooping && (this->currentPlayTime > this->maxPlayDuration))
			{
				this->Stop();
				return;
			}
			
			// Get the from-frame and to-frame
			this->DetermineFromAndToFrames();

			// Determine the normalized time 't' between the from and to frames
			const float t = (this->currentPlayTime - this->frameFrom->GetKeyframeTime()) 
						  / (this->frameTo->GetKeyframeTime() - this->frameFrom->GetKeyframeTime());

			// The number of joints should be the same for everyone
			const unsigned int numberOfJoints = this->frameMix->GetNumberOfJoints();
			assert(numberOfJoints == this->frameFrom->GetNumberOfJoints());
			assert(numberOfJoints == this->frameTo->GetNumberOfJoints());
			numberOfJoints;


			//
			// CPU
			//

			/*
			// Interpolate every bone/joint transform
			for (unsigned int i = 0; i < numberOfJoints; i++)
			{
				const AnimationJoint& fromJoint = this->frameFrom->GetReadOnlyJointAt(i);
				const AnimationJoint& toJoint = this->frameTo->GetReadOnlyJointAt(i);
				AnimationJoint& mixedJoint = this->frameMix->GetWritableJointAt(i);

				VectApp::Lerp(mixedJoint.Translation, fromJoint.Translation, toJoint.Translation, t);
				QuatApp::Slerp(mixedJoint.Rotation, fromJoint.Rotation, toJoint.Rotation, t);
				VectApp::Lerp(mixedJoint.Scale, fromJoint.Scale, toJoint.Scale, t);
			}
			//*/


			//
			// GPU
			//

			assert(frameMixerProg->GetName() == GpuProgramName::AnimFrameMixer);
			
			frameMixerProg->MakeActive();
			GpuBufferVao::Activate();
			{
				// Activate program
				frameMixerProg->SetUniform("t", t);

				// Set "from" frame buffer
				this->frameFrom->GetGpuBufferOfJoints()->ActivateAs(GpuBufferType::ArrayBuffer);
				frameMixerProg->FormatInputBufferFloat("translationA", 4, sizeof(AnimationJoint), 0 * sizeof(Vect));
				frameMixerProg->FormatInputBufferFloat("rotationA", 4, sizeof(AnimationJoint), 1 * sizeof(Vect));
				frameMixerProg->FormatInputBufferFloat("scaleA", 4, sizeof(AnimationJoint), 2 * sizeof(Vect));

				// Set "to" frame buffer
				this->frameTo->GetGpuBufferOfJoints()->ActivateAs(GpuBufferType::ArrayBuffer);
				frameMixerProg->FormatInputBufferFloat("translationB", 4, sizeof(AnimationJoint), 0 * sizeof(Vect));
				frameMixerProg->FormatInputBufferFloat("rotationB", 4, sizeof(AnimationJoint), 1 * sizeof(Vect));
				frameMixerProg->FormatInputBufferFloat("scaleB", 4, sizeof(AnimationJoint), 2 * sizeof(Vect));

				// Run the GPU Program and write results into frameMix
				frameMixerProg->Execute(this->frameMix->GetGpuBufferOfJoints());

				//AnimationJoint* feedback = new AnimationJoint[this->frameMix->GetGpuBufferOfJoints()->GetNumberOfElements()];
				//this->frameMix->GetGpuBufferOfJoints()->GetBufferData(feedback, this->frameMix->GetGpuBufferOfJoints()->GetNumberOfElements());
				//assert(feedback != nullptr);
			}
			GpuBufferVao::Unactivate();

		}
	}



	const KeyFrame& AnimationPlayback::GetCurrentFrame() const
	{
		return *(this->frameMix);
	}



	const bool AnimationPlayback::IsPlaying() const
	{
		return this->isPlaying;
	}

	const TimeUnit AnimationPlayback::GetCurrentPlayTime() const
	{
		return this->currentPlayTime;
	}

	const CString& AnimationPlayback::GetPlaybackName() const
	{
		return this->name;
	}

	const float AnimationPlayback::GetPlaybackSpeedScale() const
	{
		return this->playbackSpeedScale;
	}
	void AnimationPlayback::SetPlaybackSpeedScale(const float newScale)
	{
		assert(newScale > 0.0f);
		this->playbackSpeedScale = newScale;
	}

	const bool AnimationPlayback::IsLooping() const
	{
		return this->isLooping;
	}
	
	void AnimationPlayback::SetLoop(const bool loops)
	{
		this->isLooping = loops;
	}

	const unsigned int AnimationPlayback::GetNumberOfJoints() const
	{
		return this->frameMix->GetNumberOfJoints();
	}

	const unsigned int AnimationPlayback::GetPlaybackNameHash() const
	{
		return this->nameHash;
	}


	void AnimationPlayback::AdvanceTime(const TimeUnit& deltaTime)
	{
		this->currentPlayTime += deltaTime * this->playbackSpeedScale;

		if (this->isLooping && (this->currentPlayTime > this->maxPlayDuration))
		{
			this->currentPlayTime = this->currentPlayTime - this->maxPlayDuration;
		}
	}

	const KeyFrame* const AnimationPlayback::GetToFrame() const
	{
		return this->frameTo;
	}

	const KeyFrame* const AnimationPlayback::GetFromFrame() const
	{
		return this->frameFrom;
	}


	void AnimationPlayback::SetTime(const TimeUnit& newTime)
	{
		this->currentPlayTime += newTime;

		if (this->isLooping && (this->currentPlayTime > this->maxPlayDuration))
		{
			this->currentPlayTime = this->currentPlayTime - this->maxPlayDuration;
		}
	}

}