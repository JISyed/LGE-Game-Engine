#ifndef H_LGE_ANIMATION_KEY_FRAME
#define H_LGE_ANIMATION_KEY_FRAME

#include "AnimationJoint.h"
#include "..\TimeSystem\TimeUnit.h"
#include "..\GraphicsSystem\GpuBuffer.h"

namespace lge
{
	class KeyFrame
	{
	public:

		//
		// Big 4 + Other Ctors
		//

		// Required for array allocation. Do not use otherwise
		KeyFrame();
		// Make new keyframe with AnimationJoint array and array count
		KeyFrame(const TimeUnit frameTime, AnimationJoint* const keyframeJoints, const unsigned int numberOfJoints);
		// Move bone data into a new keyframe. Clears data in old keyframe
		KeyFrame(KeyFrame&& other);
		// Move bone data into an existing keyframe. Clears data in old keyframe
		KeyFrame& operator=(KeyFrame&& other);
		// Copy assignment
		KeyFrame& operator=(const KeyFrame& other);
		// Dtor
		~KeyFrame();




		//
		// Accessors
		//

		// Get the animation time of this keyframe
		const TimeUnit GetKeyframeTime() const;
		
		// Only the animation system should call this!
		void ManuallySetTime(const TimeUnit& newTime);

		// Get the number of animation joints in this keyframe
		const unsigned int GetNumberOfJoints() const;

		// Get a read-only reference to an AnimationJoint for the given index
		const AnimationJoint& GetReadOnlyJointAt(const unsigned int index) const;

		// Get a writable reference to an AnimationJoint for the given index
		AnimationJoint& GetWritableJointAt(const unsigned int index);

		// Get read-only array of all joints at this keyframe
		const AnimationJoint* const GetEveryJoint() const;

		// Get the GPU buffer holding this frame's joint data
		GpuBuffer* const GetGpuBufferOfJoints() const;


	private:

		//
		// Data
		//

		GpuBuffer* gpuJointsBuffer;				// The joints of this frame in GPU
		TimeUnit keyframeTime;					// The point in time of the keyframe
		unsigned int numOfJoints;				// The number of joints of this keyframe
		AnimationJoint* allJointsAtKeyframe;	// The joints of this keyframe



		//
		// Deleted Methods
		//

		// No copy
		KeyFrame(const KeyFrame& other) = delete;
		

	};
}
#endif