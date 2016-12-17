#ifndef H_LGE_CHUNK_HEADER
#define H_LGE_CHUNK_HEADER

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

// The LGE Data Header prefixed onto the binary data
struct ChunkHeader
{
	ChunkType type;
	char chunkName[CHUNK_NAME_SIZE];
	int chunkSize;
	unsigned int hashNum;

	// Default constructor
	ChunkHeader();

	// Setter for the chunkName (string copy)
	void SetChunkName(const char* const newName, const size_t newNameSize);

	// Process the command line arguments to get the name and type
	void ProcessArgs(const char* const typeStr, const char* const nameStr);

	// Process the input file to get the size and hash
	void ProcessInFile(const unsigned char* const fileBuffer, const int size);

	// Read the CHUNK_TYPE parameter into a readable enumeration
	static ChunkType CStringToChunkType(const char* const typeStr);
};

#endif