#include "CliUtility.h"
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include "md5.h"
#include <cassert>
#include "ChunkHeader.h"


//
// Static Data
//

// All the error messages in LGE
static const char* const s_errorMessages[] = {
	"Code= 0x0: No error (This should not be seen, otherwise InvokeCliError() is being used incorrectly) %s",
	"ERROR 0x1: Too many parameters provided! %s\n",
	"ERROR 0x2: Too few parameters provided! %s\n",
	"ERROR 0x3: Options need to be prefixed with a hyphen \"-\". Using \"%c\" instead\n",
	"ERROR 0x4: Unrecognized option \"%s\"\n",
	"ERROR 0x5: Option \"%s\" is being repeated\n",
	"ERROR 0x6: Chunk Type \"%s\" is undefined or spelled wrong. It's also case-sensitive\n",
	"ERROR 0x7: Chunk Name \"%s\" is too long. See usage.\n",
	"ERROR 0x8: Could not load the file \"%s\". Either it doesn't exist or its spelled wrong\n",
	"ERROR 0x9: There was a problem determining the size of the file \"%s\"",
	"ERROR 0xA: There was an error reading the file \"%s\"",
	"ERROR 0xB: There was an error closing the file \"%s\"",
	"ERROR 0xC: There was an error writing the ChunkHeader from memory into the output file \"%s\"",
	"ERROR 0xD: There was an error writing the input file into the output file \"%s\""
};



//
// Functions
//


void PrintCliHelp()
{
	printf("\nUSAGE:\n");

	printf(" MetaAppender inputFile.ext [ -t CHUNK_TYPE ] [ -n CHUNK_NAME ]\n");
	printf("\n");
	printf("      - inputFile.ext can be any binary file with any extension\n");
	//printf("      - outputFile.lge can be any name, but should have the \".lge\" extension\n");
	printf("      - [CHUNK_TYPE] can be one of the following:\n");
	printf("                * Vertices\n");
	printf("                * Triangles\n");
	printf("                * Texture\n");
	printf("                * BoundingSphere\n");
	printf("                * Animation\n");
	printf("      - [CHUNK_NAME] can be any name with max of %d characters (no spaces)\n", CHUNK_NAME_SIZE-1);
	printf("\n");
}




// Print an error message including context for the error.
// Will exit the program on the given error code.
// If no context is needed, use empty string ("").
void InvokeCliError(unsigned int errorCode, const char* const context)
{
	printf("\n");
	// Error code 3 has different formatting from the other error messages
	if (errorCode == 0x3)
	{
		printf(s_errorMessages[errorCode], context[0]);
	}
	else
	{
		printf(s_errorMessages[errorCode], context);
	}

	PrintCliHelp();

	assert(errorCode == 0);

#if LGE_CMD_PAUSE
	system("pause");
#endif
	
	exit(errorCode);
}




// Get the chunk name and type from the command line arguments. Assumes that argc is 6
void ProcessArguments(char* argv[], ChunkHeader& dataHeaderInOut)
{
	// For MetaAppender, the option arguments are the 2nd and 4th in argv
	char* const firstOption = argv[2];
	char* const secondOption = argv[4];

	// Check if the options start with a hyphen
	if (firstOption[0] != '-')
	{
		InvokeCliError(LGE_ERROR_OPTION_NO_HYPHEN, firstOption);
	}
	if (secondOption[0] != '-')
	{
		InvokeCliError(LGE_ERROR_OPTION_NO_HYPHEN, secondOption);
	}

	// Make the options lower case
	firstOption[1] = (char)tolower(firstOption[1]);
	secondOption[1] = (char)tolower(secondOption[1]);

	// Examine the options (must be -t then -n, or -n then -t)
	if (!strcmp(firstOption, "-t"))
	{
		// The second option should be -n
		if (!strcmp(secondOption, "-n"))
		{
			// 3rd argument is chunk type and 5th argument is chunk name
			dataHeaderInOut.ProcessArgs(argv[3], argv[5]);
			printf("LGE Data Chunk Name:             %s\n", argv[5]);
			printf("LGE Data Chunk Type:             %s\n", argv[3]);
		}
		// -t should not occur twice in this branch
		else if (!strcmp(secondOption, "-t"))
		{
			InvokeCliError(LGE_ERROR_REPEATING_OPTION, secondOption);
		}
		else
		{
			InvokeCliError(LGE_ERROR_UNKNOWN_OPTION, secondOption);
		}
	}
	else if (!strcmp(firstOption, "-n"))
	{
		// The second option should be -t
		if (!strcmp(secondOption, "-t"))
		{
			// 3rd argument is chunk name and 5th argument is chunk type
			dataHeaderInOut.ProcessArgs(argv[5], argv[3]);
			printf("LGE Data Chunk Name:             %s\n", argv[3]);
			printf("LGE Data Chunk Type:             %s\n", argv[5]);
		}
		// -n should not occur twice in this branch
		else if (!strcmp(secondOption, "-n"))
		{
			InvokeCliError(LGE_ERROR_REPEATING_OPTION, secondOption);
		}
		else
		{
			InvokeCliError(LGE_ERROR_UNKNOWN_OPTION, secondOption);
		}
	}
	else
	{
		InvokeCliError(LGE_ERROR_UNKNOWN_OPTION, firstOption);
	}

}



// Gets a compressed version (4 bytes) of the (16 byte) MD5 hash for the given buffer.
// Should only be called once per file/buffer
const unsigned int GetFileBufferHash(const unsigned char* const fileBuffer, const int bufferSize)
{
	return CompressedMD5Buffer(fileBuffer, bufferSize);
}

