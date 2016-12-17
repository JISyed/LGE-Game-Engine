#include "AnimationController.h"
#include <cassert>
#include "AnimationClipPlayback.h"
#include "..\GraphicsSystem\MeshRenderer.h"
#include "..\GraphicsSystem\Material.h"
#include "..\GraphicsSystem\GpuBufferVao.h"
#include "MathEngine.h"

namespace lge
{

	AnimationController::AnimationController(const AnimationSet& animationData) :
		currentPlayback(nullptr),
		finalMix(new KeyFrame(TimeUnit(DurationBasis::Zero), new AnimationJoint[animationData.GetSkeleton()->GetNumberOfJoints()], animationData.GetSkeleton()->GetNumberOfJoints())),
		playbacks(),
		animationSet(animationData),
		playState(PlayState::Stopped),
		finalMixWorldMats(nullptr)
	{
		auto itr = animationData.GetClipIterator();

		// The first clip is the default currentPlayback
		{
			AnimationClipPlayback* firstPlayback = new AnimationClipPlayback(itr.GetCurrent());
			this->playbacks.AddToBack(firstPlayback);
			this->currentPlayback = firstPlayback;
			itr.GoToNext();
			*(this->finalMix) = firstPlayback->GetCurrentFrame();
		}

		// Add the rest of the clips as playbacks
		while (!itr.IsDone())
		{
			AnimationClipPlayback* currentPlayback = new AnimationClipPlayback(itr.GetCurrent());
			this->playbacks.AddToBack(currentPlayback);
			itr.GoToNext();
		}

		this->finalMixWorldMats = new Matrix[100];

		// Create local joint matrices buffer (will get data from other parts of code)
		this->localMatricesBuffer = new GpuBuffer(GpuBufferType::TransformFeedbackBuffer,
												  GpuBufferAccess::DynamicCopy,
												  this->animationSet.GetSkeleton()->GetNumberOfJoints() + 1,
												  sizeof(Matrix),
												  nullptr
		);


		{
			Matrix identity(IDENTITY);
			this->localMatricesBuffer->SetSubRegion(0, 1, &identity.m0());
		}

		// Create global joint matrices buffer (will get data from other parts of code)
		this->globalMatricesBuffer = new GpuBuffer(GpuBufferType::ArrayBuffer,
												   GpuBufferAccess::DynamicCopy,
												   this->animationSet.GetSkeleton()->GetNumberOfJoints(),
												   sizeof(Matrix),
												   nullptr
		);


	}

	AnimationController::~AnimationController()
	{
		assert(this->finalMix != nullptr);
		delete this->finalMix;
		delete[] this->finalMixWorldMats;
		delete this->localMatricesBuffer;
		delete this->globalMatricesBuffer;
	}



	void AnimationController::Play()
	{
		this->playState = PlayState::Playing;
		this->currentPlayback->Play();
	}

	void AnimationController::Pause()
	{
		this->playState = PlayState::Paused;
		this->currentPlayback->Pause();
	}

	void AnimationController::Stop()
	{
		this->playState = PlayState::Stopped;
		this->currentPlayback->Stop();
	}


	void AnimationController::Update(const TimeUnit deltaTime)
	{
		static const TimeUnit ZERO_TIME = TimeUnit(DurationBasis::Zero);

		if (this->playState == PlayState::Playing)
		{
			assert(this->currentPlayback->IsPlaying());
			this->currentPlayback->Update(deltaTime, this->animationSet.GetSkeleton()->GetGpuProgramFrameMixer());
			if (this->currentPlayback->IsPlaying() == false)
			{
				if (this->currentPlayback->GetCurrentPlayTime() == ZERO_TIME)
				{
					this->playState = PlayState::Stopped;
				}
				else
				{
					this->playState = PlayState::Paused;
				}
			}
			else
			{
				// Copy the frame over
				*(this->finalMix) = this->currentPlayback->GetCurrentFrame();

				const KeyFrame& testFrame = this->currentPlayback->GetCurrentFrame();
				testFrame;

				// Activate joint-data-to-local-matirx program
				GpuProgram* const jointToLocalMatProg = this->animationSet.GetSkeleton()->GetGpuProgramJointToLocalMat();
				jointToLocalMatProg->MakeActive();
				// Convert the joint data into local matrices
				GpuBufferVao::Activate();
				{
					

					// Format data of final mix buffer for program
					GpuBuffer* keyframeMixBuffer = this->currentPlayback->GetCurrentFrame().GetGpuBufferOfJoints();//this->finalMix->GetGpuBufferOfJoints();
					keyframeMixBuffer->ActivateAs(GpuBufferType::ArrayBuffer);
					jointToLocalMatProg->FormatInputBufferFloat("translation", 4, sizeof(AnimationJoint), 0 * sizeof(Vect));
					jointToLocalMatProg->FormatInputBufferFloat("rotation", 4, sizeof(AnimationJoint), 1 * sizeof(Vect));
					jointToLocalMatProg->FormatInputBufferFloat("scale", 4, sizeof(AnimationJoint), 2 * sizeof(Vect));

					// Run program and write results into local matrices buffer
					jointToLocalMatProg->ExecuteRange(this->localMatricesBuffer, 1, this->animationSet.GetSkeleton()->GetNumberOfJoints());

					/*
					Matrix trans = Matrix(TRANS, 4.0f, 5.0f, 6.0f);
					trans;

					Matrix* feedback = new Matrix[keyframeMixBuffer->GetNumberOfElements()];
					keyframeMixBuffer->GetBufferData(feedback, keyframeMixBuffer->GetNumberOfElements());
					assert(feedback != nullptr);
					//*/
				}
				GpuBufferVao::Unactivate();
			}
		}
	}


	void AnimationController::CalculateWorldBoneMats(MeshRenderer* renderer)
	{
		

		//
		// CPU
		//

		/*
		// Used to calculate local transforms in "bone/joint" space
		Matrix localJointMat = Matrix(IDENTITY);
		Matrix localScale = Matrix(IDENTITY);
		Matrix localRotation = Matrix(IDENTITY);
		Matrix localTranslation = Matrix(IDENTITY);

		// Calculate the first joint (root) in world space
		localScale = Matrix(SCALE, finalMix->GetReadOnlyJointAt(0).Scale);
		localRotation = Matrix(finalMix->GetReadOnlyJointAt(0).Rotation);
		localTranslation = Matrix(TRANS, finalMix->GetReadOnlyJointAt(0).Translation);
		localJointMat = localScale * localRotation * localTranslation;
		this->finalMixWorldMats[0] = localJointMat * renderer->GetModelMatrix();

		// Calculate the rest of the joints in world space
		const unsigned int NumOfJoints = this->animationSet.GetSkeleton()->GetNumberOfJoints();
		assert(NumOfJoints <= 100);
		for (unsigned int j = 1; j < NumOfJoints; j++)
		{
			localScale = Matrix(SCALE, finalMix->GetReadOnlyJointAt(j).Scale);
			localRotation = Matrix(finalMix->GetReadOnlyJointAt(j).Rotation);
			localTranslation = Matrix(TRANS, finalMix->GetReadOnlyJointAt(j).Translation);

			localJointMat = localScale * localRotation * localTranslation;

			const unsigned int parentIdx = this->animationSet.GetSkeleton()->GetSkeletonHierarchyData()->GetParentIndexOf(j);
			this->finalMixWorldMats[j] = localJointMat * this->finalMixWorldMats[parentIdx];
		}

		// Send down the world bone matrices
		renderer->GetCurrentMaterial()->SetUniform(UniformName::JointsInWorldSpace, this->finalMixWorldMats);
		//*/


		//
		// GPU
		//


		// Activate program
		GpuProgram* const localToGlobalMatProg = this->animationSet.GetSkeleton()->GetGpuProgramLocalToGlobalMat();
		localToGlobalMatProg->MakeActive();
		GpuBufferVao::Activate();
		{
			const Matrix& modelMat = renderer->GetModelMatrix();
			localToGlobalMatProg->SetUniform("modelMat", modelMat);

			// Setup hierarchy buffer
			GpuBuffer* const hierarchyBuffer = this->animationSet.GetSkeleton()->GetGpuHierarchyBuffer();
			hierarchyBuffer->ActivateAs(GpuBufferType::ArrayBuffer);
			localToGlobalMatProg->FormatInputBufferInt("index0", 4, sizeof(Matrix), 0*sizeof(Vect));
			localToGlobalMatProg->FormatInputBufferInt("index1", 4, sizeof(Matrix), 1*sizeof(Vect));
			localToGlobalMatProg->FormatInputBufferInt("index2", 4, sizeof(Matrix), 2*sizeof(Vect));
			localToGlobalMatProg->FormatInputBufferInt("index3", 4, sizeof(Matrix), 3*sizeof(Vect));

			// Setup the local matrix buffer as a uniform block input for this program
			localToGlobalMatProg->SetInputBuffer(this->localMatricesBuffer, "ParentsBlock");

			// Run the program and write results into global matrices buffer
			localToGlobalMatProg->Execute(this->globalMatricesBuffer);
			assert(glGetError() == GL_NO_ERROR);

			//Matrix* feedback = new Matrix[globalMatricesBuffer->GetNumberOfElements()];
			//globalMatricesBuffer->GetBufferData(&feedback->m0(), globalMatricesBuffer->GetNumberOfElements());
			//assert(feedback != nullptr);
		}
		GpuBufferVao::Unactivate();
		



		// Send down the inverse bind pose
		const Matrix* const invBindPose = this->animationSet.GetSkeleton()->GetInverseBindPoseTransforms();
		renderer->GetCurrentMaterial()->SetUniform(UniformName::InverseBindPoses, invBindPose);

	}


	const KeyFrame& AnimationController::GetFinalMix() const
	{
		return *(this->finalMix);
	}



	void AnimationController::SetCurrentPlaybackCommon(AnimationPlayback* const newPlayback)
	{
		AnimationPlayback* const oldPlayback = this->currentPlayback;
		this->currentPlayback = newPlayback;

		switch (this->playState)
		{
			case PlayState::Playing:
				oldPlayback->Stop();
				this->currentPlayback->Play();
				break;
			case PlayState::Paused:
				oldPlayback->Stop();
				this->currentPlayback->Pause();
				break;
			case PlayState::Stopped:
				this->currentPlayback->Stop();
				break;
			default:
				assert(false);
				break;
		}
	}


	void AnimationController::SetCurrentPlayback(const char* const playbackName)
	{
		assert(playbackName != nullptr);
		AnimationPlayback* const playback = this->playbacks.FindDataByName(playbackName);
		assert(playback != nullptr);

		this->SetCurrentPlaybackCommon(playback);
	}

	void AnimationController::SetCurrentPlayback(const unsigned int playbackHash)
	{
		AnimationPlayback* const playback = this->playbacks.FindDataById(playbackHash);
		assert(playback != nullptr);

		this->SetCurrentPlaybackCommon(playback);
	}


	AnimationPlayback* const AnimationController::GetCurrentPlayback() const
	{
		return this->currentPlayback;
	}

	const AnimationSet& AnimationController::GetAnimationSet() const
	{
		return this->animationSet;
	}

	GpuBuffer* const AnimationController::GetGlobalMatricesGpuBuffer() const
	{
		return this->globalMatricesBuffer;
	}

}