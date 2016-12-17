#ifndef H_LGE_PKG_CHUNK_TYPE
#define H_LGE_PKG_CHUNK_TYPE
namespace lge
{
	// Defines to type of data being defined for the LGE data chunk
	enum class PackageChunkType : unsigned int
	{
		Undefined,
		Vertices = 0xA0000000,
		Trianges,
		Texture,
		BoundingSphere,
		Animation
	};
}
#endif