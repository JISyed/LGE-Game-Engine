#include "YamlCameraLoader.h"
#include "..\GraphicsSystem\Camera.h"
#include "..\GraphicsSystem\CameraManager.h"
#include "yaml-cpp\yaml.h"
#include "YamlVector4Converter.h"
#include "YamlUtilities.h"
#include "..\EngineUtilities\Screen.h"
#include <cassert>

namespace lge
{
	namespace YamlLoader
	{
		// Load cameras from a yaml file. Will automatically add to CameraManager
		// Can load 1 or multiple cameras depending on how the file was written
		void LoadCamera(const char* const yamlFilePath)
		{
			// Check if the YAML file exists. Needed to evade exceptions in yaml-cpp
			const bool fileExists = YamlUtilities::DoesFileExist(yamlFilePath);
			assert(fileExists);

			if (fileExists)
			{
				std::vector<YAML::Node> yamlDocs = YAML::LoadAllFromFile(std::string(yamlFilePath));

				// There should be at load 1 camera defined in the file
				const size_t NumOfCameras = yamlDocs.size();
				assert(NumOfCameras > 0);

				// Process every camera (defined as separate YAML docs in the 1 file)
				for (size_t currCamIdx = 0; currCamIdx < NumOfCameras; currCamIdx++)
				{
					// There should be a key node under the document root called "LGE-Camera"
					const YAML::Node& cameraNode = yamlDocs[currCamIdx]["LGE-Camera"];
					
					// Node is mispelled either in YAML or here
					assert(cameraNode.IsDefined());

					// Get Transform and Projection subnodes
					const YAML::Node& transformNode = cameraNode["Transform"];
					const YAML::Node& projectionNode = cameraNode["Projection"];
					assert(transformNode.IsDefined());
					assert(projectionNode.IsDefined());

					// Load the data off the YAML file
					const bool willBeActive = cameraNode["IsActive"].as<bool>();
					const float orbitDist = cameraNode["OrbitDistance"].as<float>();
					const Vect position = transformNode["Position"].as<Vect>();
					const Vect eulerAngles = transformNode["EulerAngles"].as<Vect>();
					const float fov = projectionNode["FOV"].as<float>();
					const float near = projectionNode["NearClip"].as<float>();
					const float far = projectionNode["FarClip"].as<float>();

					// Create a camera with these properties
					Camera* newCamera = new Camera();
					newCamera->SetOrbitDistance(orbitDist);
					newCamera->SetPosition(position);
					newCamera->SetEulerAngles(eulerAngles);
					newCamera->SetProjection(fov, Screen::GetAspectRatio(), near, far);

					// Add the camera to the manager
					CameraManager::Add(newCamera);

					// If specified, make this camera the active camera
					if (willBeActive)
					{
						newCamera->MakeActive();
					}
				}
			}
		}
	}
}