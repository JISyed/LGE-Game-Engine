#ifndef H_LGE_YAML_CAMERA_LOADER
#define H_LGE_YAML_CAMERA_LOADER
namespace lge
{
	// Forward declare
	class Camera;

	// All YamlLoader functions
	namespace YamlLoader
	{
		// Load cameras from a yaml file. Will automatically add to CameraManager
		// Can load 1 or multiple cameras depending on how the file was written
		void LoadCamera(const char* const yamlFilePath);
	}
}
#endif