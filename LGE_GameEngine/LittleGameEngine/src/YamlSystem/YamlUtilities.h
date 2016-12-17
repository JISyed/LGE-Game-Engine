#ifndef H_LGE_YAML_UTILITIES
#define H_LGE_YAML_UTILITIES
namespace lge
{
	// A collection of utility functions to help in processing YAML files
	namespace YamlUtilities
	{
		// Check if the YAML file exists before opening it. Needed to avoid excpetions
		const bool DoesFileExist(const char* const yamlFileName);

		// Prevents namespace pollution from asserts. Not meant to be used outside the YAML system
		void YamlSystemAssertion(const bool condition);
	}
}
#endif