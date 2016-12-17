#ifndef LGE_CAMERA_MANAGER_H
#define LGE_CAMERA_MANAGER_H

#include "..\EngineFoundation\ResourseRegistry.h"
#include "..\AbstractDataTypes\GenericList.h"
#include "..\YamlSystem\enumUseYamlType.h"

namespace lge
{
	// Forward declares
	class Camera;
	class Matrix;
	class Vect;


	// Manages every camera that currently exists in the game
	class CameraManager : public ResourceRegistry
	{
	public:

		//
		// Ctor / Dtor
		//

		CameraManager();
		virtual ~CameraManager();


		//
		// Contracts
		//

		virtual void Load() override;
		virtual void Unload() override;
		virtual void Update() override;



		//
		// Methods
		//

		// Change the project universally for every existing camera
		//void SetAllProjections(const Matrix& newProjection);
		void SetAllProjections(const float newYFieldOfView,
							   const float newAspectRatio,
							   const float newNearClip,
							   const float newFarClip);

		// Draw the view fustrum of every camera, if they have one
		void DrawCameraGizmos();


		// Automatically loads cameras from YAML definition file
		// Located in /res/cameras/
		void Create(LgeUseYaml_t useYaml, const char* const cameraDefinitionYamlFile);


		//
		// Static Methods
		//

		// Find any camera by ID (cannot be 0)
		static Camera& Find(const unsigned int cameraId);

		// Factory for a new Camera. Automatically added
		static Camera * const Create(const Vect& position, const Vect& eulerAngles);
		
		// Get the current number of camera managed
		static const int GetNumberOfCameras();

		// Must be dynamically allocated, for it will be deleted by this manager later
		static void Add(Camera* newCamera);

	private:

		//
		// Data
		//

		GenericList<Camera> cameraList;
		float yFOV;
		float aspectRatio;
		float nearClip;
		float farClip;


		//
		// Static Data
		//

		static CameraManager* singletonInstance;



		//
		// Deleted Methods
		//

		// No copy ctor
		CameraManager(const CameraManager& other) = delete;

		// No copy assignment
		CameraManager& operator=(const CameraManager& other) = delete;

		// No move ctor
		CameraManager(CameraManager&& other) = delete;

		// No move assignment
		CameraManager& operator=(CameraManager&& other) = delete;

	};
}
#endif