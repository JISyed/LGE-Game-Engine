#include "DirectoryUtility.h"
#ifdef _WIN32
	#include <windows.h>
#else
	#include <dirent.h>
#endif
#include <cstdio>
#include <cstring>

#define MAX_DIR_NAME_SIZE 300

using namespace std;




#ifdef _WIN32
void GetAllFilenamesWindows(const char* const baseDirectory, const char* const extName, std::vector<std::string>& names)
{
	// Create the file search query for the base directory for files with the given extension name
	char search_path[MAX_DIR_NAME_SIZE];
	_snprintf_s(search_path, MAX_DIR_NAME_SIZE, _TRUNCATE, "%s\\*.%s", baseDirectory, extName);

	// Find the first .lge file in the directory
	WIN32_FIND_DATA directoryIterator; 
	HANDLE directoryEntry = FindFirstFile(search_path, &directoryIterator);

	// Assuming the first .lge file was found
	if (directoryEntry != INVALID_HANDLE_VALUE)
	{ 
		// Get every .lge file name
		do 
		{ 
			// ... Only if it's a file
			if (!(directoryIterator.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				size_t fileNameLen = strlen(directoryIterator.cFileName);

				if (directoryIterator.cFileName[fileNameLen - 1] == 'e' &&
					directoryIterator.cFileName[fileNameLen - 2] == 'g' &&
					directoryIterator.cFileName[fileNameLen - 3] == 'l' &&
					directoryIterator.cFileName[fileNameLen - 4] == '.')
				{
					names.push_back(directoryIterator.cFileName);
				}
			} 
		} 
		// Continue if the next .lge file can be found
		while (FindNextFile(directoryEntry, &directoryIterator));
		
		// Close the file handle when finished
		FindClose(directoryEntry);
	} 
}
#endif


#ifndef _WIN32
// NOTE: Not tested
void GetAllFilenamesUnix(const char* const baseDirectory, const char* const extName, std::vector<std::string>& names)
{
	DIR* directory;
	struct dirent* dirEntry;
	size_t entryNameLength = 0;
	int c = 0;

	// Open the directory
	directory = opendir(baseDirectory);
	if (directory != 0)
	{
		// Get all the files of .lge extension
		while ((dirEntry = readdir(directory)) != 0)
		{
			entryNameLength = strlen(dirEntry->d_name);
			c = entryNameLength;
			while (dirEntry->d_name[c] != '.')
			{
				if (c <= 0)
				{
					break;
				}

				c--;
			}

			if (c <= 0)
			{
				continue;
			}

			c++;
			int e = 0;
			bool extensionMatches = false;
			while (c != entryNameLength + 1)
			{
				if (dirEntry->d_name[c] != extName[e])
				{
					break;
				}

				if (extName[e] == '\0')
				{
					extensionMatches = true;
				}

				c++;
				e++;
			}

			if (extensionMatches)
			{
				// Finally add the file name into the collection
				names.push_back(dirEntry->d_name);
			}
		}

		// Close the directory
		closedir(directory);
	}
}
#endif


void GetAllFilenames(const char* const baseDirectory, const char* const extName, std::vector<std::string>& names)
{
#ifdef _WIN32
	GetAllFilenamesWindows(baseDirectory, extName, names);
#else
	GetAllFilenamesUnix(baseDirectory, extName, names);
#endif
}