#ifndef H_LGE_PKG_RESOURCE_UNPACKER
#define H_LGE_PKG_RESOURCE_UNPACKER
#include "File.h"
#include "enumPackageChunkType.h"
#include "enumUseUnpackerType.h"
#include "VboHeader.h"
#include "EboHeader.h"
#include "TextureHeader.h"
#include "..\CollisionSystem\BoundingSphere.h"
#include "..\AnimationSystem\AnimationSet.h"

namespace lge
{
	// Forward declares
	struct PackageHeader;
	struct PackageChunkHeader;

	// Static class to load game resources from the compiled .lgepkg package
	class ResourceUnpacker
	{
	public:
		
		// Read a vertex buffer from the resource package given a name. Returns true if found and loaded properly. Buffer must be deleted by user!
		static const bool ReadVertices(const char* const ResourceName, VboHeader& vertDataHeader, float*& vertBuffer);

		// Read a triangle buffer from the resource package given a name. Returns true if found and loaded properly. Buffer must be deleted by user!
		static const bool ReadTriangles(const char* const ResourceName, EboHeader& triDataHeader, unsigned int*& triBuffer);

		// Read a texture buffer from the resource package given a name. Returns true if found and loaded properly. Buffer must be deleted by user!
		static const bool ReadTexture(const char* const ResourceName, TextureHeader& texDataHeader, unsigned char*& texBuffer);

		// Read a bounding sphere from the resource package given a name. Returns true if found and loaded properly.
		static const bool ReadBoundingSphere(const char* const ResourceName, BoundingSphere& sphere);

		// Read an entire animation set from the resource package given a name. Returns true if found and loaded properly.
		static const bool ReadAnimationSet(const char* const ResourceName, AnimationSet*& animationSet);

	private:

		// Open the package file with all the game resources in it ( must close with ClosePackageFile() )
		static const bool OpenPackageFile(FileHandle& file, const char* const packagePath);

		// Close the package file
		static const bool ClosePackageFile(FileHandle& file);

		// Read the .lgepkg Package Header. Returns true if reading is successful
		static const bool ReadPackageHeader(FileHandle& file, PackageHeader& pkgHdr);

		// Find the package chunk holding the inqured dat given a chunk name and chunk type. Returns true if the chunk was found.
		static const bool FindPackageChunk(FileHandle& file, PackageChunkHeader& chunkHdr, const int TotalChunks, const PackageChunkType InquiredType, const char* const InquredName);

		// Handle complicated logic behind deserializing animation data
		static void DeserializeAnimationData(FileHandle& file, AnimationSet*& animationSet);
	};
}
#endif