#include "CameraManager.h"
#include <cassert>

#include "Camera.h"
#include "..\EngineUtilities\Screen.h"

#include <string>
#include "..\YamlSystem\YamlCameraLoader.h"


#define LGE_CAMERA_DATA_PATH	"res/cameras/"

namespace lge
{
	//
	// Static Data
	//

	CameraManager* CameraManager::singletonInstance = nullptr;




	//
	// Methods
	//

	CameraManager::CameraManager() :
		cameraList(),
		yFOV(50.0f),
		aspectRatio(0.5f),
		nearClip(0.1f),
		farClip(100.0f)
	{
		assert(CameraManager::singletonInstance == nullptr);
		CameraManager::singletonInstance = this;
	}

	// VIRTUAL
	CameraManager::~CameraManager()
	{
		// List must be emptied before destroying manager!
		assert(this->cameraList.GetNumberOfElements() == 0);

		// Manager must exist in singleton link!
		assert(CameraManager::singletonInstance != nullptr);
		CameraManager::singletonInstance = nullptr;
	}




	// VIRTUAL
	void CameraManager::Load()
	{
		this->Create(UseYaml, "lge_all_cameras.yml");
	}


	// VIRTUAL
	void CameraManager::Unload()
	{
		while (this->cameraList.GetNumberOfElements() != 0)
		{
			Camera* oldCamera = this->cameraList.RemoveFront();
			delete oldCamera;
		}
	}


	// VIRTUAL
	void CameraManager::Update()
	{
		// This block will assert if the active camera is not set
		{
			Camera& camCheck = Camera::GetActiveCamera();
			camCheck;
		}

		GenericListIterator<Camera> itr = this->cameraList.GetIterator();
		Camera* currCam = itr.First();
		while (!itr.IsDone())
		{
			currCam->Update();
			currCam = itr.Next();
		}
	}


	// Draw the view fustrum of every camera, if they have one
	void CameraManager::DrawCameraGizmos()
	{
		GenericListIterator<Camera> itr = this->cameraList.GetIterator();
		Camera* currCam = itr.First();
		while (!itr.IsDone())
		{
			currCam->DrawGizmos();
			currCam = itr.Next();
		}
	}


	/*void CameraManager::SetAllProjections(const Matrix& newProjection)
	{
		GenericListIterator<Camera> itr = this->cameraList.GetIterator();
		Camera* currCam = itr.First();
		while (!itr.IsDone())
		{
			currCam->SetProjection(newProjection);
			currCam = itr.Next();
		}
	}*/
	void CameraManager::SetAllProjections(const float newYFieldOfView,
										  const float newAspectRatio,
										  const float newNearClip,
										  const float newFarClip)
	{
		this->yFOV = newYFieldOfView;
		this->aspectRatio = newAspectRatio;
		this->nearClip = newNearClip;
		this->farClip = newFarClip;

		if (this->cameraList.GetNumberOfElements() > 0)
		{
			GenericListIterator<Camera> itr = this->cameraList.GetIterator();
			Camera* currCam = itr.First();
			while (!itr.IsDone())
			{
				currCam->SetProjection(newYFieldOfView,
									   newAspectRatio,
									   newNearClip,
									   newFarClip);
				currCam = itr.Next();
			}
		}
	}


	// Automatically loads cameras from YAML definition file
	// Located in /res/cameras/
	void CameraManager::Create(LgeUseYaml_t useYaml, const char* const cameraDefinitionYamlFile)
	{
		useYaml;
		assert(useYaml == UseYaml);

		const std::string fullPath = std::string(LGE_CAMERA_DATA_PATH) + std::string(cameraDefinitionYamlFile);
		YamlLoader::LoadCamera(fullPath.c_str());
	}


	// STATIC
	// Camera must be dynamically allocated, for it will be deleted by this manager later
	void CameraManager::Add(Camera* newCamera)
	{
		assert(newCamera != nullptr);
		CameraManager::singletonInstance->cameraList.AddFront(newCamera);
	}


	// STATIC
	// Find any camera by ID (cannot be 0)
	Camera& CameraManager::Find(const unsigned int cameraId)
	{
		return *(CameraManager::singletonInstance->cameraList.FindById(cameraId));
	}


	// STATIC
	// Factory for a new Camera. Automatically added
	Camera * const CameraManager::Create(const Vect& position, const Vect& eulerAngles)
	{
		assert(CameraManager::singletonInstance != nullptr);

		Camera* newCamera = new Camera();
		newCamera->SetPosition(position);
		newCamera->SetEulerAngles(eulerAngles);
		newCamera->SetProjection(CameraManager::singletonInstance->yFOV,
								 CameraManager::singletonInstance->aspectRatio,
								 CameraManager::singletonInstance->nearClip,
								 CameraManager::singletonInstance->farClip);

		CameraManager::singletonInstance->Add(newCamera);

		return newCamera;
	}
	
	// STATIC
	// Get the current number of camera managed
	const int CameraManager::GetNumberOfCameras()
	{
		assert(CameraManager::singletonInstance != nullptr);

		return CameraManager::singletonInstance->cameraList.GetNumberOfElements();
	}


}