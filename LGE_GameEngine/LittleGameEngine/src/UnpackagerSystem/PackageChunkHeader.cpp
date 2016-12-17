#include "PackageChunkHeader.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

namespace lge
{
	PackageChunkHeader::PackageChunkHeader()
	{
		this->chunkName[LGE_PKG_CHUNK_NAME_SIZE - 1] = '\0';
	}




}