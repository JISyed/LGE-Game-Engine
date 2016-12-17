#ifndef H_LGE_CHUNK_HDR
#define H_LGE_CHUNK_HDR

#define CHUNK_NAME_SIZE 32

// Defines to type of data being defined for the LGE data chunk
enum class ChunkType : unsigned int
{
	Undefined,
	Vertices = 0xA0000000,
	Trianges,
	Texture,
	BoundingSphere,
	Animation
};

// The LGE Data Header prefixed inside an LGE file
// (The full implementation is in MetaAppender. It's only being used here for reading data)
struct ChunkHeader
{
	ChunkType type;
	char chunkName[CHUNK_NAME_SIZE];
	int chunkSize;
	unsigned int hashNum;
};

#endif