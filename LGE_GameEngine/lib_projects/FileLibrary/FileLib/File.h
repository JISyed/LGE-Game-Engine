#ifndef FILE_H
#define FILE_H

#include <windows.h> // win32

// Make the assumption of c-char strings, not UNICODE
// 32 bit files, not supporting 64 bits

namespace lge
{
	// Designates if the file handle should read and/or write the file
	enum class FileMode : unsigned int
	{
		FILE_READ = 0xA0000000,
		FILE_WRITE,
		FILE_READ_WRITE
	};

	// Designates the relative position that the file should seek from
	enum class FileSeek : unsigned int
	{
		FILE_SEEK_BEGIN = 0xC0000000,
		FILE_SEEK_CURRENT,
		FILE_SEEK_END
	};

	// Designates error codes for every file action.
	// Includes a "SUCCESS" if there is no error.
	enum class FileError : unsigned int
	{
		FILE_SUCCESS = 0xB0000000,
		FILE_OPEN_FAIL,
		FILE_CLOSE_FAIL,
		FILE_WRITE_FAIL,
		FILE_READ_FAIL,
		FILE_SEEK_FAIL,
		FILE_TELL_FAIL,
		FILE_FLUSH_FAIL
	};

	typedef HANDLE FileHandle;

	// The file input/output helper
	class File
	{
	public:

		// Open a file into a given file handle, for the given filename.
		// Also needs to know if you are reading or writing the file.
		// If fileMustExist is false, open() will fail if the file does not exist
		static FileError open(FileHandle &fh, const char * const fileName, FileMode mode, bool fileMustExist = false);
		
		// Close an already open file given a valid file handle
		static FileError close(FileHandle fh);

		// Write data from a memory buffer into a file given the handle, buffer, and how much data in bytes
		static FileError write(FileHandle fh, const void * const buffer, const size_t inSize);
		
		// Read data from a file into a memory buffer given a handle, buffer, and how much data in bytes
		static FileError read(FileHandle fh, void * const _buffer, const size_t _size);
		
		// Move the location in the file where file actions should be done from.
		// Seek can either be relative to the beginning of the file,
		// the end of the file, or from the current location in the file.
		static FileError seek(FileHandle fh, FileSeek seek, int offset);
		
		// Get the current location in the file where file actions will be done from
		static FileError tell(FileHandle fh, int &offset);
		
		// Force the write buffer for the given file to get "flushed" into the storage drive.
		// Usually done automatically when closing a file.
		static FileError flush(FileHandle fh);


	private:

		//
		// Private methods
		//

		// Convert our file mode designation into Windows' designation
		static DWORD getWindowsFileMode(FileMode ourFileMode);

		// Convert our file seek designation into Windows' designation
		static DWORD getWindowsMoveMethod(FileSeek ourSeekMethod);
	};
}

#endif