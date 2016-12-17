#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "File.h"
#include <string>

// MetaAppender should only have 5 parameters + the program itself
#define LGE_ARGC 6

#include "ChunkHeader.h"
#include "CliUtility.h"

/*
	MetaAppender.exe:
	---------
	*  Parameter formats:
		*  MetaAppender inputFile.ext outFile.ext < options >
	*  Input and output files
		*  inputFile
			i. raw binary fileName with extension
			*  example: aa.bin
	*  options parameters (order isn’t important)
		*  [-t CHUNK_TYPE ]
			i. set chunk type
		*  [-n CHUNK_NAME ]
			i. set chunk name (max 19 characters)
*/

using namespace lge;

// Extry point: MAIN
int main(int argc, char* argv[])
{
	///// CMD Processing


	// Check if too many arguments
	if (argc > LGE_ARGC)
	{
		InvokeCliError(LGE_ERROR_TOO_MUCH_ARGS, "");
	}

	// Check if too few parameters
	if (argc < LGE_ARGC)
	{
		InvokeCliError(LGE_ERROR_TOO_FEW_ARGS, "");
	}

	// Get the two file names (they are always the first two arguments)
	const char* inFileName = argv[1];
	//const char* outFileName = argv[2];

	printf("Original File:        %s\n", inFileName);
	std::string outFileName(inFileName);
	outFileName.append(".lge");
	printf("Converted LGE File:   %s\n", outFileName.c_str());



	// Get the name and type of chunk from the cmd arguments
	ChunkHeader cHdr;
	ProcessArguments(argv, cHdr);


	////// Reading In File

	printf("\nReading Original File...\n");

	// Load the input file into a buffer
	FileHandle inFile;
	FileError fileErrorCode = FileError::FILE_SUCCESS;
	fileErrorCode = File::open(inFile, inFileName, FileMode::FILE_READ);
	if (fileErrorCode != FileError::FILE_SUCCESS)
	{
		//assert(fileErrorCode != FILE_OPEN_FAIL);
		InvokeCliError(LGE_ERROR_FILE_OPEN, inFileName);
	}


	// Get the size of the file
	int inFileSize = 0;
	fileErrorCode = File::seek(inFile, FileSeek::FILE_SEEK_END, 0);
	if (fileErrorCode != FileError::FILE_SUCCESS)
	{
		assert(fileErrorCode != FileError::FILE_SEEK_FAIL);
		FileError closeCode = File::close(inFile);
		assert(closeCode != FileError::FILE_CLOSE_FAIL);
		closeCode;
		InvokeCliError(LGE_ERROR_FILE_SIZE, inFileName);
	}
	fileErrorCode = File::tell(inFile, inFileSize);
	if (fileErrorCode != FileError::FILE_SUCCESS)
	{
		assert(fileErrorCode != FileError::FILE_TELL_FAIL);
		FileError closeCode = File::close(inFile);
		assert(closeCode != FileError::FILE_CLOSE_FAIL);
		closeCode;
		InvokeCliError(LGE_ERROR_FILE_SIZE, inFileName);
	}
	fileErrorCode = File::seek(inFile, FileSeek::FILE_SEEK_BEGIN, 0);
	if (fileErrorCode != FileError::FILE_SUCCESS)
	{
		assert(fileErrorCode != FileError::FILE_SEEK_FAIL);
		FileError closeCode = File::close(inFile);
		assert(closeCode != FileError::FILE_CLOSE_FAIL);
		closeCode;
		InvokeCliError(LGE_ERROR_FILE_SIZE, inFileName);
	}


	// Read the file contents into memory
	unsigned char* inFileBuffer = new unsigned char[inFileSize];
	assert(inFileBuffer != nullptr);
	fileErrorCode = File::read(inFile, inFileBuffer, (size_t)inFileSize);
	if (fileErrorCode != FileError::FILE_SUCCESS)
	{
		assert(fileErrorCode != FileError::FILE_READ_FAIL);
		FileError closeCode = File::close(inFile);
		assert(closeCode != FileError::FILE_CLOSE_FAIL);
		closeCode;
		delete[] inFileBuffer;
		InvokeCliError(LGE_ERROR_FILE_READ, inFileName);
	}

	// Close the file, it's not needed anymore
	fileErrorCode = File::close(inFile);
	if (fileErrorCode != FileError::FILE_SUCCESS)
	{
		assert(fileErrorCode != FileError::FILE_CLOSE_FAIL);
		delete[] inFileBuffer;
		InvokeCliError(LGE_ERROR_FILE_CLOSE, inFileName);
	}



	// Get the hash and size of the chunk
	cHdr.ProcessInFile(inFileBuffer, inFileSize);

	printf("    LGE data block size:   %d bytes (0x%X in hex)\n", cHdr.chunkSize, cHdr.chunkSize);
	printf("    Data block hash:         0x%X\n", cHdr.hashNum);







	/////// Writing Out File

	printf("Writing Converted LGE File...\n");

	// Create the output file from given cmd argument (for writing)
	FileHandle outFile;
	fileErrorCode = File::open(outFile, outFileName.c_str(), FileMode::FILE_WRITE);
	if (fileErrorCode != FileError::FILE_SUCCESS)
	{
		assert(fileErrorCode != FileError::FILE_OPEN_FAIL);
		delete[] inFileBuffer;
		InvokeCliError(LGE_ERROR_FILE_OPEN, outFileName.c_str());
	}


	// Write the chunk header into the file first
	fileErrorCode = File::write(outFile, &cHdr, sizeof(ChunkHeader));
	if (fileErrorCode != FileError::FILE_SUCCESS)
	{
		assert(fileErrorCode != FileError::FILE_WRITE_FAIL);
		FileError closeCode = File::close(inFile);
		assert(closeCode != FileError::FILE_CLOSE_FAIL);
		closeCode;
		delete[] inFileBuffer;
		InvokeCliError(LGE_ERROR_CHUNK_HDR_WRITE, outFileName.c_str());
	}


	// Write the In File data into the Out File (right after the chunk header)
	fileErrorCode = File::write(outFile, inFileBuffer, inFileSize);
	if (fileErrorCode != FileError::FILE_SUCCESS)
	{
		assert(fileErrorCode != FileError::FILE_WRITE_FAIL);
		FileError closeCode = File::close(inFile);
		assert(closeCode != FileError::FILE_CLOSE_FAIL);
		closeCode;
		delete[] inFileBuffer;
		InvokeCliError(LGE_ERROR_FILE_WRITE, outFileName.c_str());
	}


	// Close the file, it's not needed anymore
	fileErrorCode = File::close(outFile);
	if (fileErrorCode != FileError::FILE_SUCCESS)
	{
		assert(fileErrorCode != FileError::FILE_CLOSE_FAIL);
		delete[] inFileBuffer;
		InvokeCliError(LGE_ERROR_FILE_CLOSE, outFileName.c_str());
	}




	delete[] inFileBuffer;

	printf("\nSuccess!\n");

#if LGE_CMD_PAUSE
	printf("\n");
	system("pause");
#endif

	return 0;
}