#include "ChunkHeader.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "CliUtility.h"

ChunkHeader::ChunkHeader()
{
	memset(this->chunkName, 0x0, CHUNK_NAME_SIZE);
	this->chunkName[CHUNK_NAME_SIZE - 1] = '\0';
}


void ChunkHeader::SetChunkName(const char* const newName, const size_t newNameSize)
{
	// Trying to get around dumb strncpy-is-unsafe warning
#if defined _WIN32
	strncpy_s(this->chunkName, CHUNK_NAME_SIZE, newName, newNameSize);
#else
	int toCopy = newNameSize > CHUNK_NAME_SIZE ? CHUNK_NAME_SIZE : newNameSize;
	strncpy(this->chunkName, newName, toCopy);
#endif
	this->chunkName[CHUNK_NAME_SIZE - 1] = '\0';
}


// Process the command line arguments to get name and type
void ChunkHeader::ProcessArgs(const char* const typeStr, const char* const nameStr)
{
	// Set the chunk type
	this->type = ChunkHeader::CStringToChunkType(typeStr);
	if (this->type == ChunkType::Undefined)
	{
		InvokeCliError(LGE_ERROR_UNKNOWN_TYPE, typeStr);
	}


	// Set the chunk name

	// +1 because strlen() doesn't include the null char at the end
	const size_t nameStrSize = strlen(nameStr) + 1;

	if (nameStrSize > CHUNK_NAME_SIZE)
	{
		InvokeCliError(LGE_ERROR_NAME_TOO_BIG, nameStr);
	}

	this->SetChunkName(nameStr, nameStrSize);
}


// Process the input file to get the size and hash
void ChunkHeader::ProcessInFile(const unsigned char* const fileBuffer, const int size)
{
	// Set the chunk size
	this->chunkSize = size;

	// Calculate the compressed MD5 hash (not full MD5 hash) of the file
	this->hashNum = GetFileBufferHash(fileBuffer, size);
}




// STATIC
ChunkType ChunkHeader::CStringToChunkType(const char* const typeStr)
{
	ChunkType type = ChunkType::Undefined;

	if (!strcmp(typeStr, "Vertices"))
	{
		type = ChunkType::Vertices;
	}
	else if (!strcmp(typeStr, "Triangles"))
	{
		type = ChunkType::Trianges;
	}
	else if (!strcmp(typeStr, "Texture"))
	{
		type = ChunkType::Texture;
	}
	else if (!strcmp(typeStr, "BoundingSphere"))
	{
		type = ChunkType::BoundingSphere;
	}
	else if (!strcmp(typeStr, "Animation"))
	{
		type = ChunkType::Animation;
	}

	return type;
}