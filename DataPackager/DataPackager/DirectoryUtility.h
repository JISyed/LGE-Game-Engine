#ifndef H_LGE_DIR_UTIL
#define H_LGE_DIR_UTIL

#include <vector>
#include <string>


// The working directory of DataPackager
#define LGE_WORKING_DIR "."

// The file extension for vodka chunks (no dot)
#define LGE_EXT_FOR_CHUNKS "lge"



void GetAllFilenames(const char* const baseDirectory, const char* const extName, std::vector<std::string>& names);

#endif