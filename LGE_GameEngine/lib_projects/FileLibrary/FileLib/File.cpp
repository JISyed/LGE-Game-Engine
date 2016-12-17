#include <assert.h>
#include "File.h"

// Can be a combination of 0, FILE_SHARE_READ, or FILE_SHARE_WRITE
#define DEFAULT_SHARE_MODE 0

// Create Depositions include:
// CREATE_NEW, CREATE_ALWAYS, OPEN_EXISTING, OPEN_ALWAYS, or TRUNCATE_EXISTING


namespace lge
{
	// Open a file into a given file handle, for the given filename.
	// Also needs to know if you are reading or writing the file.
	// If fileMustExist is false, open() will fail if the file does not exist
	FileError File::open(FileHandle &fh, const char * const fileName, FileMode mode, bool fileMustExist)
	{
		DWORD createDeposition = 0;

		if (mode == FileMode::FILE_READ_WRITE || mode == FileMode::FILE_WRITE)
		{
			if (fileMustExist)
			{
				createDeposition = TRUNCATE_EXISTING;
			}
			else
			{
				createDeposition = CREATE_ALWAYS;
			}
		}
		else if (mode == FileMode::FILE_READ)
		{
			if (fileMustExist)
			{
				createDeposition = OPEN_EXISTING;
			}
			else
			{
				createDeposition = OPEN_ALWAYS;
			}
		}

		fh = CreateFile(fileName,
						getWindowsFileMode(mode),
						DEFAULT_SHARE_MODE,
						NULL,		// Security Attributes
						createDeposition,
						FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
						NULL		// Attribute template file
						);

		if (fh == INVALID_HANDLE_VALUE)
		{
			return FileError::FILE_OPEN_FAIL;
		}

		return FileError::FILE_SUCCESS;
	}

	// Close an already open file given a valid file handle
	FileError File::close(const FileHandle fh)
	{
		// Hopefully the handle is for a file

		// Had to bypass a stupid invalid handle exception
#ifndef NDEBUG
		BY_HANDLE_FILE_INFORMATION fInfo;
		if (GetFileInformationByHandle(fh, &fInfo) && CloseHandle(fh))
		{
			return FileError::FILE_SUCCESS;
		}
#else
		BOOL closeSuccess = CloseHandle(fh);
		if (closeSuccess)
		{
			return FileError::FILE_SUCCESS;
		}
#endif

		return FileError::FILE_CLOSE_FAIL;
	}

	// Write data from a memory buffer into a file given the handle, buffer, and how much data in bytes
	FileError File::write(FileHandle fh, const void * const buffer, const size_t inSize)
	{
		// Check for null buffer
		if (buffer == nullptr)
		{
			return FileError::FILE_WRITE_FAIL;
		}

		// Write into the file
		DWORD bytesWritten = 0;
		BOOL writeSuccess = WriteFile(fh,
									  buffer,
									  inSize,
									  &bytesWritten,
									  NULL	// Overlapped struct
									  );

		// Verify
		if (!writeSuccess || bytesWritten < inSize)
		{
			return FileError::FILE_WRITE_FAIL;
		}

		return FileError::FILE_SUCCESS;
	}

	// Read data from a file into a memory buffer given a handle, buffer, and how much data in bytes
	FileError File::read(FileHandle fh, void * const buffer, const size_t inSize)
	{
		// Check for null buffer
		if (buffer == nullptr)
		{
			return FileError::FILE_READ_FAIL;
		}

		// Read from file into the buffer.
		// Assumes that the buffer is truely the size given by "inSize"
		DWORD bytesRead = 0;
		BOOL readSuccess = ReadFile(fh,
									buffer,
									inSize,
									&bytesRead,
									NULL  // Overlapped struct
									);

		// Verify
		if (!readSuccess)
		{
			return FileError::FILE_READ_FAIL;
		}

		// Too strict?
		//*
		if (bytesRead < inSize)
		{
			return FileError::FILE_READ_FAIL;
		}
		//*/

		return FileError::FILE_SUCCESS;
	}

	// Move the location in the file where file actions should be done from.
	// Seek can either be relative to the beginning of the file,
	// the end of the file, or from the current location in the file.
	FileError File::seek(FileHandle fh, FileSeek seek, int offset)
	{
		// Move the file pointer (aka seek)
		DWORD newFilePtr = SetFilePointer(fh,
										  offset,
										  NULL,	// High order 32-bits of 64 bit offset
										  getWindowsMoveMethod(seek)
										  );

		// Validate
		if (newFilePtr == INVALID_SET_FILE_POINTER)
		{
			return FileError::FILE_SEEK_FAIL;
		}

		return FileError::FILE_SUCCESS;
	}

	// Get the current location in the file where file actions will be done from
	FileError File::tell(FileHandle fh, int &offset)
	{
		// Using Windows' seek function to do a tell. Weird...
		DWORD currOffset = SetFilePointer(fh,
										  0,
										  NULL,	// High order 32-bits of 64 bit offset
										  FILE_CURRENT
										  );

		// Validate first
		if (currOffset == INVALID_SET_FILE_POINTER)
		{
			return FileError::FILE_TELL_FAIL;
		}

		// Then record file position
		offset = currOffset;

		return FileError::FILE_SUCCESS;
	}


	// Force the write buffer for the given file to get "flushed" into the storage drive.
	// Usually done automatically when closing a file.
	FileError File::flush(FileHandle fh)
	{
		BOOL flushSuccess = FlushFileBuffers(fh);

		if (!flushSuccess)
		{
			return FileError::FILE_FLUSH_FAIL;
		}

		return FileError::FILE_SUCCESS;
	}



	//
	// Private Methods
	//

	// Convert our file mode designation into Windows' designation
	DWORD File::getWindowsFileMode(FileMode ourFileMode)
	{
		DWORD accessCode = GENERIC_READ;

		switch (ourFileMode)
		{
			case FileMode::FILE_READ:
				accessCode = GENERIC_READ;
				break;
			case FileMode::FILE_WRITE:
				accessCode = GENERIC_WRITE;
				break;
			case FileMode::FILE_READ_WRITE:
				accessCode = GENERIC_READ | GENERIC_WRITE;
				break;
		}

		return accessCode;
	}

	// Convert our file seek designation into Windows' designation
	DWORD File::getWindowsMoveMethod(FileSeek ourSeekMethod)
	{
		DWORD moveMethod = 0;

		switch (ourSeekMethod)
		{
			case FileSeek::FILE_SEEK_BEGIN:
				moveMethod = FILE_BEGIN;
				break;
			case FileSeek::FILE_SEEK_CURRENT:
				moveMethod = FILE_CURRENT;
				break;
			case FileSeek::FILE_SEEK_END:
				moveMethod = FILE_END;
				break;
		}

		return moveMethod;
	}

}
