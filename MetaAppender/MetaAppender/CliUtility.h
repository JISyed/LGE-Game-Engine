#ifndef H_LGE_CLI_UTILITY
#define H_LGE_CLI_UTILITY

#include "ChunkHeader.h"

//
// Macros
//

// There are too many command line arguments
#define LGE_ERROR_TOO_MUCH_ARGS 0x1

// There are too few command line arguments
#define LGE_ERROR_TOO_FEW_ARGS 0x2

// The option argument isn't using a hyphen
#define LGE_ERROR_OPTION_NO_HYPHEN 0x3

// The option argument is unknown to LGE and cannot be processed
#define LGE_ERROR_UNKNOWN_OPTION 0x4

// The option argument was provided more than once and cannot be processed
#define LGE_ERROR_REPEATING_OPTION 0x5

// The type of LGE data chunk provided is invalid (not supported)
#define LGE_ERROR_UNKNOWN_TYPE 0x6

// The name of the LGE data chunk is too long (must be max of 19 chars)
#define LGE_ERROR_NAME_TOO_BIG 0x7

// The file could not be opened
#define LGE_ERROR_FILE_OPEN 0x8

// There was a problem determining the size of the opened file
#define LGE_ERROR_FILE_SIZE 0x9

// There was a problem reading data from the opened file
#define LGE_ERROR_FILE_READ 0xA

// There was a problem closing the opened file
#define LGE_ERROR_FILE_CLOSE 0xB

// There was a problem writing the chunk header
#define LGE_ERROR_CHUNK_HDR_WRITE 0xC

// There was a problme writing the in-file data into the out-file
#define LGE_ERROR_FILE_WRITE 0xD


// Macro switch for enabling cmd pausing
#define LGE_CMD_PAUSE 0



//
// Functions
//


// Print the usage information for this program
void PrintCliHelp();

// Print an error message including context for the error.
// Will exit the program on the given error code.
// If no context is needed, use empty string ("").
void InvokeCliError(unsigned int errorCode, const char* const context);

// Get the chunk name and type from the command line arguments. Assumes that argc is 7
void ProcessArguments(char* argv[], ChunkHeader& dataHeaderInOut);

// Gets a compressed version (4 bytes) of the (16 byte) MD5 hash for the given buffer.
// Should only be called once per file/buffer
const unsigned int GetFileBufferHash(const unsigned char* const fileBuffer, const int bufferSize);

#endif