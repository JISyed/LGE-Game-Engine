#include "KeyFrame.h"
#include <cassert>

namespace lge
{
	// Required for array allocation. Do not use otherwise
	KeyFrame::KeyFrame() :
		gpuJointsBuffer(nullptr),
		keyframeTime(),
		numOfJoints(0u),
		allJointsAtKeyframe(nullptr)
	{
	}

	// Make new keyframe with AnimationJoint array and array count
	KeyFrame::KeyFrame(const TimeUnit frameTime, AnimationJoint* const keyframeJoints, const unsigned int numberOfJoints) :
		gpuJointsBuffer(nullptr),
		keyframeTime(frameTime),
		numOfJoints(numberOfJoints),
		allJointsAtKeyframe(keyframeJoints)
	{
		this->gpuJointsBuffer = new GpuBuffer(GpuBufferType::ArrayBuffer,
											  GpuBufferAccess::StaticRead,
											  numberOfJoints,
											  sizeof(AnimationJoint),
											  keyframeJoints);
	}

	// Move bone data into a new keyframe. Clears data in old keyframe
	KeyFrame::KeyFrame(KeyFrame&& other) :
		gpuJointsBuffer(other.gpuJointsBuffer),
		keyframeTime(other.keyframeTime),
		numOfJoints(other.numOfJoints),
		allJointsAtKeyframe(other.allJointsAtKeyframe)
	{
		// Unlink the data of the old keyframe
		other.numOfJoints = 0u;
		other.allJointsAtKeyframe = nullptr;
		other.gpuJointsBuffer = nullptr;
	}

	// Move bone data into an existing keyframe. Clears data in old keyframe
	KeyFrame& KeyFrame::operator=(KeyFrame&& other)
	{
		if (this == &other)
		{
			return *this;
		}

		// Move data into this new keyframe from the other
		this->gpuJointsBuffer = other.gpuJointsBuffer;
		this->keyframeTime = other.keyframeTime;
		this->numOfJoints = other.numOfJoints;
		this->allJointsAtKeyframe = other.allJointsAtKeyframe;

		// Unlink the data of the old keyframe
		other.numOfJoints = 0u;
		other.allJointsAtKeyframe = nullptr;
		other.gpuJointsBuffer = nullptr;

		return *this;
	}

	//*
	// Copy assignment
	KeyFrame& KeyFrame::operator=(const KeyFrame& other)
	{
		if (this == &other)
		{
			return *this;
		}

		assert(other.numOfJoints == this->numOfJoints);

		this->keyframeTime = other.keyframeTime;
		this->numOfJoints = other.numOfJoints;

		// Copy every joint
		for (unsigned int i = 0; i < this->numOfJoints; i++)
		{
			this->allJointsAtKeyframe[i] = other.allJointsAtKeyframe[i];
		}

		// Copy GPU buffer for joints
		if (this->gpuJointsBuffer == nullptr)
		{
			this->gpuJointsBuffer = new GpuBuffer(GpuBufferType::ArrayBuffer,
												  GpuBufferAccess::StaticRead,
												  this->numOfJoints,
												  sizeof(AnimationJoint),
												  this->allJointsAtKeyframe);
		}
		else
		{
			this->gpuJointsBuffer->SetSubRegion(0, this->numOfJoints, this->allJointsAtKeyframe);
		}

		return *this;
	}
	//*/

	// Dtor
	KeyFrame::~KeyFrame()
	{
		if (this->allJointsAtKeyframe != nullptr)
		{
			delete[] this->allJointsAtKeyframe;
		}
		if (this->gpuJointsBuffer != nullptr)
		{
			delete this->gpuJointsBuffer;
		}
	}







	// Get the animation time of this keyframe
	const TimeUnit KeyFrame::GetKeyframeTime() const
	{
		return this->keyframeTime;
	}

	// Only the animation system should call this!
	void KeyFrame::ManuallySetTime(const TimeUnit& newTime)
	{
		this->keyframeTime = newTime;
	}

	// Get the number of animation joints in this keyframe
	const unsigned int KeyFrame::GetNumberOfJoints() const
	{
		return this->numOfJoints;
	}

	// Get a read-only reference to an AnimationJoint for the given index
	const AnimationJoint& KeyFrame::GetReadOnlyJointAt(const unsigned int index) const
	{
		assert(index < this->numOfJoints);
		return this->allJointsAtKeyframe[index];
	}

	// Get a writable reference to an AnimationJoint for the given index
	AnimationJoint& KeyFrame::GetWritableJointAt(const unsigned int index)
	{
		assert(index < this->numOfJoints);
		return this->allJointsAtKeyframe[index];
	}


	// Get read-only array of all joints at this keyframe
	const AnimationJoint* const KeyFrame::GetEveryJoint() const
	{
		return this->allJointsAtKeyframe;
	}


	// Get the GPU buffer holding this frame's joint data
	GpuBuffer* const KeyFrame::GetGpuBufferOfJoints() const
	{
		assert(this->gpuJointsBuffer != nullptr);
		return this->gpuJointsBuffer;
	}

}