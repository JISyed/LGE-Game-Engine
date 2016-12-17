#ifndef H_LGE_ANIMATION_SKELETON
#define H_LGE_ANIMATION_SKELETON
#include "JointHierarchyTable.h"
#include "JointNameTable.h"
#include "..\AbstractDataTypes\CString.h"
#include "Matrix.h"
#include "..\GraphicsSystem\GpuBuffer.h"
#include "..\GraphicsSystem\GpuProgram.h"

namespace lge
{

	// Represents the data to construct an animation skeleton (does not actually do any animations on its own)
	class AnimationSkeleton
	{
	public:
		
		//
		// Ctor + Dtor
		//
		
		AnimationSkeleton(const unsigned int newHash, const unsigned int numberOfJoints, JointHierarchyTable* const hierarchy, JointNameTable* const jointNameTable, Matrix* const invBindPoseMats, unsigned int* const jointLevelArray, const char* const skeletonName);
		~AnimationSkeleton();


		//
		// Accessors
		//

		// Get the hash identifier of this skeleton (based off the exported name)
		const unsigned int GetHashId() const;

		// Get the number of joints in this skeleton
		const unsigned int GetNumberOfJoints() const;

		// Get child-parent index lookup table for this skeleton's joints
		const JointHierarchyTable* const GetSkeletonHierarchyData() const;

		// Get the name loopup table of this skeleton's joints
		const JointNameTable* const GetJointNames() const;

		// Get the exported name of this skeleton
		const CString& GetName() const;

		// Get the inverse bind pose transforms for every joint in the skeleton
		const Matrix* const GetInverseBindPoseTransforms() const;

		// Get the lookup table for joint levels
		const unsigned int* const GetJointLevelsTable() const;

		// Get the hierarchy buffer for GPU animation
		GpuBuffer* const GetGpuHierarchyBuffer() const;

		// Get the LocalToGlobalMat GpuProgram
		GpuProgram* const GetGpuProgramLocalToGlobalMat() const;

		// Get the JointToLocalMat GpuProgram
		GpuProgram* const GetGpuProgramJointToLocalMat() const;

		// Get the FrameMixer GpuProgram
		GpuProgram* const GetGpuProgramFrameMixer() const;


	private:

		//
		// Data
		//

		GpuBuffer* gpuHierarchy;				// The hierarchy table in the GPU
		GpuProgram* gpuProgLocalToGlobal;		// Program shader for calculating local to global joint matrices
		GpuProgram* gpuProgFrameMixer;			// Program shader to mix multiple keyframes together
		GpuProgram* gpuProgJointToLocal;		// Program shader ot calculate joint daata into local joint matrices
		unsigned int hash;						// Unique identifier based off exported name
		unsigned int numOfJoints;				// The number of joints in this skeleton
		JointHierarchyTable* skeletonHierarchy;	// The lookup table of joint child-parent indices
		JointNameTable* jointNames;				// The lookup table of joint names
		unsigned int* jointLevels;				// The lookup table for joint hierachy levels
		Matrix*	inverseBindPoseTransforms;		// For skinning
		CString name;							// The unique name of this skeleton (set by exporter)
		


		//
		// Deleted Methods
		//

		// No default ctor
		AnimationSkeleton() = delete;

		// No copy
		AnimationSkeleton(const AnimationSkeleton& other) = delete;

		// No copy
		AnimationSkeleton& operator=(const AnimationSkeleton& other) = delete;

	};
}
#endif