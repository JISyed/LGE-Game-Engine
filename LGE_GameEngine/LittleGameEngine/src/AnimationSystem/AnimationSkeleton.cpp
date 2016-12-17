#include "AnimationSkeleton.h"
#include <cassert>
#include "MathEngine.h"

namespace lge
{
	AnimationSkeleton::AnimationSkeleton(const unsigned int newHash, const unsigned int numberOfJoints, JointHierarchyTable* const hierarchy, JointNameTable* const jointNameTable, Matrix* const invBindPoseMats, unsigned int* const jointLevelArray, const char* const skeletonName) :
		hash(newHash),
		numOfJoints(numberOfJoints),
		skeletonHierarchy(hierarchy),
		jointNames(jointNameTable),
		jointLevels(nullptr),
		inverseBindPoseTransforms(nullptr),
		name(skeletonName)
	{
		assert(hierarchy != nullptr);
		assert(jointNameTable != nullptr);
		assert(skeletonName != nullptr);
		assert(invBindPoseMats != nullptr);
		assert(numberOfJoints == hierarchy->GetSize());
		assert(numberOfJoints == jointNameTable->GetSize());
		assert(numberOfJoints <= 100);	// Will not support more than 100 bones!

		// Used to calculate the number of levels in the hierarchy
		unsigned int highestLevel = 0;

		this->inverseBindPoseTransforms = new Matrix[100];
		this->jointLevels = new unsigned int[numberOfJoints];
		for (unsigned int i = 0; i < numberOfJoints; i++)
		{
			this->inverseBindPoseTransforms[i] = invBindPoseMats[i];
			this->jointLevels[i] = jointLevelArray[i];

			if (highestLevel < this->jointLevels[i])
			{
				highestLevel = this->jointLevels[i];
			}
		}

		// Will not support skeleton hierarchy with level depth greater than 16
		assert(highestLevel <= 16);

		// Setup the hierarchy buffer for GPU (complicated)
		const unsigned int hierarchyBufferSize = this->numOfJoints * 16;
		unsigned int* hierarchyBuffer = new unsigned int[hierarchyBufferSize]();
		unsigned int jointIndex = 1;
		for (unsigned int j = 0; j < this->numOfJoints-1; j++)
		{
			hierarchyBuffer[jointIndex * 16] = jointIndex + 1;
			const unsigned int parentIndex = this->skeletonHierarchy->GetParentIndexOf(jointIndex);
			for (unsigned int i = 0; i < 15; i++)
			{
				hierarchyBuffer[jointIndex * 16 + 1 + i] = hierarchyBuffer[parentIndex * 16 + i];
			}
			jointIndex++;
		}

		// Create GPU hierarchy buffer with new data
		this->gpuHierarchy = new GpuBuffer(GpuBufferType::ArrayBuffer, 
										   GpuBufferAccess::DynamicCopy, 
										   hierarchyBufferSize, 
										   sizeof(float), 
										   hierarchyBuffer
		);


		// Create GPU program to calculate local matrices into global matrices
		const GLchar* const outputNamesL2G[] = {"global"};
		this->gpuProgLocalToGlobal = new GpuProgram("res/shaders/localToGlobalMat.ps.glsl",
													GpuProgramName::AnimLocalToWorldMatrix,
													1,
													outputNamesL2G
		);

		// Create GPU program to calculate joint data into local matrices
		const GLchar* const outputNamesJ2L[] = {"matrix"};
		this->gpuProgJointToLocal = new GpuProgram("res/shaders/jointToLocalMat.ps.glsl",
												   GpuProgramName::AnimJointToLocalMatrix,
												   1,
												   outputNamesJ2L
		);

		// Create GPU program to mix keyframes together
		const GLchar* const outputNamesM[] = {"mixedTranslation", "mixedRotation", "mixedScale"};
		this->gpuProgFrameMixer = new GpuProgram("res/shaders/mixer.ps.glsl",
												 GpuProgramName::AnimFrameMixer,
												 3,
												 outputNamesM
		);
		
	}

	AnimationSkeleton::~AnimationSkeleton()
	{
		delete this->skeletonHierarchy;
		delete this->jointNames;
		delete[] this->inverseBindPoseTransforms;
		delete[] this->jointLevels;
		delete this->gpuHierarchy;
		delete this->gpuProgLocalToGlobal;
		delete this->gpuProgJointToLocal;
		delete this->gpuProgFrameMixer;
	}




	// Get the hash identifier of this skeleton (based off the exported name)
	const unsigned int AnimationSkeleton::GetHashId() const
	{
		return this->hash;
	}

	// Get the number of joints in this skeleton
	const unsigned int AnimationSkeleton::GetNumberOfJoints() const
	{
		return this->numOfJoints;
	}

	// Get child-parent index lookup table for this skeleton's joints
	const JointHierarchyTable* const AnimationSkeleton::GetSkeletonHierarchyData() const
	{
		return this->skeletonHierarchy;
	}

	// Get the name loopup table of this skeleton's joints
	const JointNameTable* const AnimationSkeleton::GetJointNames() const
	{
		return this->jointNames;
	}

	// Get the exported name of this skeleton
	const CString& AnimationSkeleton::GetName() const
	{
		return this->name;
	}

	// Get the inverse bind pose transforms for every joint in the skeleton
	const Matrix* const AnimationSkeleton::GetInverseBindPoseTransforms() const
	{
		return this->inverseBindPoseTransforms;
	}

	// Get the lookup table for joint levels
	const unsigned int* const AnimationSkeleton::GetJointLevelsTable() const
	{
		return this->jointLevels;
	}


	// Get the hierarchy buffer for GPU animation
	GpuBuffer* const AnimationSkeleton::GetGpuHierarchyBuffer() const
	{
		return this->gpuHierarchy;
	}


	// Get the LocalToGlobalMat GpuProgram
	GpuProgram* const AnimationSkeleton::GetGpuProgramLocalToGlobalMat() const
	{
		return this->gpuProgLocalToGlobal;
	}

	// Get the JointToLocalMat GpuProgram
	GpuProgram* const AnimationSkeleton::GetGpuProgramJointToLocalMat() const
	{
		return this->gpuProgJointToLocal;
	}

	// Get the FrameMixer GpuProgram
	GpuProgram* const AnimationSkeleton::GetGpuProgramFrameMixer() const
	{
		return this->gpuProgFrameMixer;
	}

}