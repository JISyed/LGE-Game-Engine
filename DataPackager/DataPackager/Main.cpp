#include <cstdio>
#include <cstdlib>
#include "File.h"
#include <cassert>
#include <vector>
#include <string>

#include "CliUtility.h"
#include "PackageHeader.h"
#include "DirectoryUtility.h"
#include "ChunkHeader.h"

#define LGE_ARGC 6

/*
	DataPackager.exe:
	---------
	*  Parameter formats:
		*  DataPackager outFile.ext < options >
	*  Input and output files
		*  ( inputFiles assumed *.lge in the directory)
			i. Chunks with extension *.lge
				*  example: aa.lge
		*  outFile
			i. Serial Package Unifier objects fileName with extension
				*  example: runtime.lgepkg
	*  options parameters (order isn’t important)
		*  [-n PACKAGE_NAME ]
			i. set package name
			ii. max 19 characters
		*  [-v VERSION_STRING ]
			i. set version string
			ii. max 19 characters
*/

using namespace lge;

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

	// Get the file name of the package (always the first argument)
	const char* pkgFileName = argv[1];

	printf("Package File:      %s\n", pkgFileName);



	// Get the name and type of chunk from the cmd arguments
	PackageHeader pkgHdr;
	ProcessArguments(argv, pkgHdr);


	////// Reading In Files

	// A "list" of file names
	std::vector<std::string> chunkFiles;


	printf("\nSearching for .%s files...\n", LGE_EXT_FOR_CHUNKS);
	
	// Get all the .lge file names
	GetAllFilenames(LGE_WORKING_DIR, LGE_EXT_FOR_CHUNKS, chunkFiles);


	// Stop if there are no .lge files to process
	if (chunkFiles.size() < 1)
	{
		InvokeCliError(LGE_ERROR_NO_LGE_FILES, LGE_WORKING_DIR);
	}


	printf("Getting .%s chunk sizes...\n", LGE_EXT_FOR_CHUNKS);

	// Determine the biggest chunk file (in bytes) and total size of all chunks
	int largestChunkSize = 0;
	int totalChunkSize = 0;

	{
		char largestChunkName[CHUNK_NAME_SIZE];
		unsigned int largestChunkIndex = 0;
		int currentSize = 0;
		FileHandle hChunkFile;
		FileError errorCode = FileError::FILE_SUCCESS;
		ChunkHeader cHdr;
		for (unsigned int i = 0; i < chunkFiles.size(); i++)
		{
			errorCode = File::open(hChunkFile, chunkFiles[i].c_str(), FileMode::FILE_READ);
			if (errorCode != FileError::FILE_SUCCESS)
			{
				assert(errorCode != FileError::FILE_OPEN_FAIL);
				InvokeCliError(LGE_ERROR_FILE_OPEN, chunkFiles[i].c_str());
			}
			
			errorCode = File::read(hChunkFile, &cHdr, sizeof(ChunkHeader));
			if (errorCode != FileError::FILE_SUCCESS)
			{
				assert(errorCode != FileError::FILE_READ_FAIL);
				FileError closeCode = File::close(hChunkFile);
				assert(closeCode == FileError::FILE_SUCCESS);
				closeCode;
				InvokeCliError(LGE_ERROR_FILE_READ, chunkFiles[i].c_str());
			}
			
			errorCode = File::close(hChunkFile);
			if (errorCode != FileError::FILE_SUCCESS)
			{
				assert(errorCode != FileError::FILE_CLOSE_FAIL);
				InvokeCliError(LGE_ERROR_FILE_CLOSE, chunkFiles[i].c_str());
			}
			

			currentSize = cHdr.chunkSize;
			totalChunkSize += currentSize + sizeof(ChunkHeader);
			if (currentSize > largestChunkSize)
			{
				largestChunkSize = currentSize;
				largestChunkIndex = i;
				#ifdef _WIN32
					strncpy_s(largestChunkName, CHUNK_NAME_SIZE, cHdr.chunkName, CHUNK_NAME_SIZE);
				#else
					strncpy(largestChunkName, cHdr.chunkName, CHUNK_NAME_SIZE);
				#endif
				largestChunkName[CHUNK_NAME_SIZE - 1] = '\0';
			}
		}

		largestChunkSize += sizeof(ChunkHeader);
		printf(".%s files found:     %d\n", LGE_EXT_FOR_CHUNKS, chunkFiles.size());
		printf("Total .%s files:     %d bytes (0x%X in hex)\n", LGE_EXT_FOR_CHUNKS, totalChunkSize, totalChunkSize);
		printf("Largest .%s file:    %s (%s) = %d bytes\n", LGE_EXT_FOR_CHUNKS, chunkFiles[largestChunkIndex].c_str(), largestChunkName, largestChunkSize);
	}

	// Put chunk size data into package header
	pkgHdr.totalSize = totalChunkSize;
	pkgHdr.numChunks = chunkFiles.size();





	/////// Writing package


	printf("Packing .%s files into \"%s\"...\n", LGE_EXT_FOR_CHUNKS, pkgFileName);


	// Create a file for the package
	FileHandle hPkgFile;
	FileError fileError;

	// Load the package file to write into it
	fileError = File::open(hPkgFile, pkgFileName, FileMode::FILE_WRITE);
	if (fileError != FileError::FILE_SUCCESS)
	{
		assert(fileError != FileError::FILE_OPEN_FAIL);
		InvokeCliError(LGE_ERROR_FILE_OPEN, pkgFileName);
	}


	// Write the package header first
	fileError = File::write(hPkgFile, &pkgHdr, sizeof(PackageHeader));
	if (fileError != FileError::FILE_SUCCESS)
	{
		assert(fileError != FileError::FILE_WRITE_FAIL);
		FileError closeCode = File::close(hPkgFile);
		assert(closeCode == FileError::FILE_SUCCESS);
		closeCode;
		InvokeCliError(LGE_ERROR_PKG_HDR_WRITE, pkgFileName);
	}



	// Create a file-reading buffer that is the size of the largest chunk.
	// This is so that all .lge files can be read into the same buffer
	unsigned char* chunkReadingBuffer = new unsigned char[largestChunkSize];


	
	// Write every .lge chunk file into the package
	FileHandle hLgeFile;
	int lgeFileSize = 0;
	for (unsigned int i = 0; i < chunkFiles.size(); i++)
	{
		// Open LGE file
		fileError = File::open(hLgeFile, chunkFiles[i].c_str(), FileMode::FILE_READ);
		if (fileError != FileError::FILE_SUCCESS)
		{
			assert(fileError != FileError::FILE_OPEN_FAIL);
			delete[] chunkReadingBuffer;
			FileError closeCode = File::close(hPkgFile);
			assert(closeCode == FileError::FILE_SUCCESS);
			closeCode;
			InvokeCliError(LGE_ERROR_FILE_OPEN, chunkFiles[i].c_str());
		}

		// Get file size
		fileError = File::seek(hLgeFile, FileSeek::FILE_SEEK_END, 0);
		assert(fileError != FileError::FILE_SEEK_FAIL);
		fileError = File::tell(hLgeFile, lgeFileSize);
		assert(fileError != FileError::FILE_TELL_FAIL);
		fileError = File::seek(hLgeFile, FileSeek::FILE_SEEK_BEGIN, 0);
		assert(fileError != FileError::FILE_SEEK_FAIL);
		assert(lgeFileSize <= largestChunkSize);

		// Read LGE file
		fileError = File::read(hLgeFile, chunkReadingBuffer, lgeFileSize);
		if (fileError != FileError::FILE_SUCCESS)
		{
			assert(fileError != FileError::FILE_READ_FAIL);
			delete[] chunkReadingBuffer;
			FileError closeCode = File::close(hPkgFile);
			assert(closeCode == FileError::FILE_SUCCESS);
			closeCode = File::close(hLgeFile);
			assert(closeCode == FileError::FILE_SUCCESS);
			closeCode;
			InvokeCliError(LGE_ERROR_FILE_READ, chunkFiles[i].c_str());
		}

		// Close LGE file
		fileError = File::close(hLgeFile);
		if (fileError != FileError::FILE_SUCCESS)
		{
			assert(fileError != FileError::FILE_CLOSE_FAIL);
			delete[] chunkReadingBuffer;
			FileError closeCode = File::close(hPkgFile);
			assert(closeCode == FileError::FILE_SUCCESS);
			closeCode;
			InvokeCliError(LGE_ERROR_FILE_CLOSE, chunkFiles[i].c_str());
		}

		// Write LGE data into package
		fileError = File::write(hPkgFile, chunkReadingBuffer, lgeFileSize);
		if (fileError != FileError::FILE_SUCCESS)
		{
			assert(fileError != FileError::FILE_WRITE_FAIL);
			delete[] chunkReadingBuffer;
			FileError closeCode = File::close(hPkgFile);
			assert(closeCode == FileError::FILE_SUCCESS);
			closeCode;
			InvokeCliError(LGE_ERROR_FILE_WRITE, chunkFiles[i].c_str());
		}

		printf("     - %s\n", chunkFiles[i].c_str());
	}


	// Close the package file and reading buffer
	delete[] chunkReadingBuffer;

	fileError = File::close(hPkgFile);
	if (fileError != FileError::FILE_SUCCESS)
	{
		assert(fileError != FileError::FILE_CLOSE_FAIL);
		InvokeCliError(LGE_ERROR_FILE_CLOSE, pkgFileName);
	}


	printf("\nSuccess!\n");

#if LGE_CMD_PAUSE
	printf("\n");
	system("pause");
#endif

	return 0;
}