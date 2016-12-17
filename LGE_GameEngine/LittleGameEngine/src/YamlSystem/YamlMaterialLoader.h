#ifndef H_LGE_YAML_MATERIAL_LOADER
#define H_LGE_YAML_MATERIAL_LOADER
namespace lge
{
	// Forward declare
	class Material;

	// All YamlLoader functions
	namespace YamlLoader
	{
		// Load a material from file. Will be returned only 1 Material
		Material* const LoadMaterial(const char* const yamlFilePath);
	}
}
#endif