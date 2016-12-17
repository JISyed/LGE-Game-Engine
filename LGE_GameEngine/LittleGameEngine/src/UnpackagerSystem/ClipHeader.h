#ifndef H_LGE_PKG_ANIM_CLIP_HDR
#define H_LGE_PKG_ANIM_CLIP_HDR
#include "Str64.h"
#include "..\TimeSystem\TimeUnit.h"

namespace lge
{
	// Header for a data chunk containing an AnimationClip
	struct ClipHdr
	{
		TimeUnit maxTime;			// Maximum time of the clip
		unsigned int nameHash;		// The hash of the name of this clip
		unsigned int numKeyFrames;	// The number of KeyFrames in this clip
		unsigned int doesLoop;		// Does this clip loop (should be 1 or 0)
		Str64 name;					// The name of this clip

		// Get ClipHdr::doesLoop as a bool
		const bool DoesLoop() const
		{
			if (this->doesLoop == 0)
			{
				return false;
			}

			return true;
		}

	};
}
#endif