#include "YamlUtilities.h"
#include "yaml-cpp\yaml.h"
#include "File.h"					// For testing file existance
#include <cassert>

namespace lge
{
	namespace YamlUtilities
	{
		// Check if the YAML file exists before opening it. Needed to avoid excpetions
		const bool DoesFileExist(const char* const yamlFileName)
		{
			bool doesFileExist = false;
			
			// Unfortunately, yaml-cpp library will throw an exception if
			// the YAML file cannot be found. So use the file library to
			// see if the YAML file exists before using yaml-cpp to open it
			FileHandle file;

			// Try to open the file
			FileError errorCode = File::open(file, yamlFileName, FileMode::FILE_READ, false);

			if (errorCode == FileError::FILE_SUCCESS)
			{
				// It exists. Close the file
				 FileError closeError = File::close(file);
				 assert(closeError != FileError::FILE_CLOSE_FAIL); closeError;

				 doesFileExist = true;
			}

			return doesFileExist;
		}


		// Prevents namespace pollution from asserts. Not meant to be used outside the YAML system
		void YamlSystemAssertion(const bool condition)
		{
			// Go up the call stack!!!
			assert(condition);
			condition;
		}

	}
}