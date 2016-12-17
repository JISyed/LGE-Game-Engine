#ifndef H_LGE_PKG_CHUNK_HEADER
#define H_LGE_PKG_CHUNK_HEADER
#include "enumPackageChunkType.h"
// This number must be the same as CHUNK_NAME_SIZE inside MetaAppender(new vodka)
#define LGE_PKG_CHUNK_NAME_SIZE 32
namespace lge
{
	// The LGE Data Header prefixed onto the binary data
	struct PackageChunkHeader
	{
		PackageChunkType type;
		char chunkName[LGE_PKG_CHUNK_NAME_SIZE];
		int chunkSize;
		unsigned int hashNum;

		// Default constructor
		PackageChunkHeader();
	};
}
#endif