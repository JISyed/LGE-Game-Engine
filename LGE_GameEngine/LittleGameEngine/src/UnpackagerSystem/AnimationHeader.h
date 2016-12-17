#ifndef H_LGE_PKG_ANIMATION_HDR
#define H_LGE_PKG_ANIMATION_HDR
#include "Str64.h"

namespace lge
{
	// Header for a file containing an AnimationSet
	struct AnimationHdr
	{
		unsigned int nameHash;		// The hash of the name of the skeleton
		unsigned int numOfJoints;	// The number of joints in the skeleton
		unsigned int numOfClips;	// The number of clips in this set
		Str64 name;					// The name of the skeleton
	};
}
#endif