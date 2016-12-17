#include "CameraController.h"

#include "Camera.h"
#include "CameraManager.h"
#include "..\InputSystem\Keyboard.h"
#include "..\EngineUtilities\Time.h"

namespace lge
{
	CameraController::CameraController() :
		translationSpeed(7.0f),
		rotationSpeed(1.5f),
		orbitSpeed(1.0f),
		currCameraId(1),
		ctrlMode(CameraControlMode::FreeStrafe),
		isInitialized(false)
	{
	}

	CameraController::~CameraController()
	{
	}

	void CameraController::Init()
	{
		if (!this->isInitialized)
		{
			this->isInitialized = true;

			// Initialize here
			
		}
	}

	void CameraController::Update()
	{
		// Camera Control Mode
		this->UpdateMode();

		// Orbit Distance Changes
		this->UpdateOrbitalDistance();

		// Camera Movement
		this->UpdateMovement();

		// Camera Switching
		this->UpdateCameraSwitching();
	}




	void CameraController::UpdateMode()
	{
		if (Input::Keyboard::GetKeyDown(Input::Key::Enter))
		{
			if (this->ctrlMode == CameraControlMode::FreeStrafe)
			{
				this->ctrlMode = CameraControlMode::Orbit;
			}
			else
			{
				this->ctrlMode = CameraControlMode::FreeStrafe;
			}
		}
	}



	void CameraController::UpdateMovement()
	{
		if (this->ctrlMode == CameraControlMode::FreeStrafe)
		{
			this->MoveInFreeStrafe();
		}
		else
		{
			this->MoveInOrbit();
		}
	}



	void CameraController::UpdateCameraSwitching()
	{
		if (Input::Keyboard::GetKeyDown(Input::Key::P))
		{
			this->currCameraId++;
			if (CameraManager::GetNumberOfCameras() < currCameraId)
			{
				this->currCameraId = 1;
			}

			Camera& newCamera = CameraManager::Find((unsigned int) this->currCameraId);
			newCamera.MakeActive();
		}
	}


	void CameraController::UpdateOrbitalDistance()
	{
		Camera& activeCamera = Camera::GetActiveCamera();
		float orbitDistance;
		const float orbDistChangeSpeed = 3.0f;
		const float maxOrbitDistance = 15.0f;
		const float minOrbitDistance = 1.0f;
		if (Input::Keyboard::GetKey(Input::Key::O))
		{
			orbitDistance = activeCamera.GetOrbitDistance();
			orbitDistance += orbDistChangeSpeed * Time::GetDeltaTimeInSeconds();
			activeCamera.SetOrbitDistance(orbitDistance);
			if (orbitDistance > maxOrbitDistance)
			{
				activeCamera.SetOrbitDistance(maxOrbitDistance);
			}
		}
		if (Input::Keyboard::GetKey(Input::Key::L))
		{
			orbitDistance = activeCamera.GetOrbitDistance();
			orbitDistance -= orbDistChangeSpeed * Time::GetDeltaTimeInSeconds();
			activeCamera.SetOrbitDistance(orbitDistance);
			if (orbitDistance < minOrbitDistance)
			{
				activeCamera.SetOrbitDistance(minOrbitDistance);
			}
		}
	}



	void CameraController::MoveInFreeStrafe()
	{
		Camera& activeCamera = Camera::GetActiveCamera();


		// Rotation
		if (Input::Keyboard::GetKey(Input::Key::ArrowLeft))
		{
			Vect newEuler = activeCamera.GetTransform().GetEulerAngles();
			newEuler.y() = newEuler.y() + (this->rotationSpeed * Time::GetDeltaTimeInSeconds());
			activeCamera.SetEulerAngles(newEuler);

		}

		if (Input::Keyboard::GetKey(Input::Key::ArrowRight))
		{
			Vect newEuler = activeCamera.GetTransform().GetEulerAngles();
			newEuler.y() = newEuler.y() - (this->rotationSpeed * Time::GetDeltaTimeInSeconds());
			activeCamera.SetEulerAngles(newEuler);
		}


		// Translation
		if (Input::Keyboard::GetKey(Input::Key::A))
		{
			Vect move = activeCamera.GetTransform().GetPosition() + (activeCamera.GetTransform().GetRightDirection() * (-1.0f * this->translationSpeed * Time::GetDeltaTimeInSeconds() ));
			activeCamera.SetPosition(move);
		}

		if (Input::Keyboard::GetKey(Input::Key::D))
		{
			Vect move = activeCamera.GetTransform().GetPosition() + (activeCamera.GetTransform().GetRightDirection() * (1.0f * this->translationSpeed * Time::GetDeltaTimeInSeconds() ));
			activeCamera.SetPosition(move);
		}

		if (Input::Keyboard::GetKey(Input::Key::W))
		{
			Vect move = activeCamera.GetTransform().GetPosition() + (activeCamera.GetTransform().GetForwardDirection() * (1.0f * this->translationSpeed * Time::GetDeltaTimeInSeconds() ));
			activeCamera.SetPosition(move);
		}

		if (Input::Keyboard::GetKey(Input::Key::S))
		{
			Vect move = activeCamera.GetTransform().GetPosition() + (activeCamera.GetTransform().GetForwardDirection() * (-1.0f * this->translationSpeed * Time::GetDeltaTimeInSeconds() ));
			activeCamera.SetPosition(move);
		}

		if (Input::Keyboard::GetKey(Input::Key::ArrowUp))
		{
			Vect move = activeCamera.GetTransform().GetPosition() + (activeCamera.GetTransform().GetUpDirection() * (1.0f * this->translationSpeed * Time::GetDeltaTimeInSeconds() ));
			activeCamera.SetPosition(move);
		}

		if (Input::Keyboard::GetKey(Input::Key::ArrowDown))
		{
			Vect move = activeCamera.GetTransform().GetPosition() + (activeCamera.GetTransform().GetUpDirection() * (-1.0f * this->translationSpeed * Time::GetDeltaTimeInSeconds() ));
			activeCamera.SetPosition(move);
		}
	}


	void CameraController::MoveInOrbit()
	{
		Camera& activeCamera = Camera::GetActiveCamera();

		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		if (Input::Keyboard::GetKey(Input::Key::ArrowUp))
		{
			// Get orbital data from the camera
			activeCamera.GetOrbitPoints(up, tar, pos, upNorm, forwardNorm, rightNorm, activeCamera.GetOrbitDistance());

			// Calculate matrices needed to orbit
			Matrix tM(MatrixTransType::TRANS, tar);
			Matrix tReverseM(MatrixTransType::TRANS, -tar);
			Matrix rM(RotAxisAngleType::ROT_AXIS_ANGLE, rightNorm, this->orbitSpeed * Time::GetDeltaTimeInSeconds());
			Matrix finalM = tReverseM * rM * tM;

			// Transform the orbital points to a new orientation
			up = up * finalM;
			pos = pos * finalM;
			tar = tar * finalM;

			// Set the new orbital data to the camera
			activeCamera.SetOrbitPoints(up, tar, pos);
		}

		if (Input::Keyboard::GetKey(Input::Key::ArrowDown))
		{
			// Get orbital data from the camera
			activeCamera.GetOrbitPoints(up, tar, pos, upNorm, forwardNorm, rightNorm, activeCamera.GetOrbitDistance());

			// Calculate matrices needed to orbit
			Matrix tM(MatrixTransType::TRANS, tar);
			Matrix tReverseM(MatrixTransType::TRANS, -tar);
			Matrix rM(RotAxisAngleType::ROT_AXIS_ANGLE, rightNorm, -this->orbitSpeed * Time::GetDeltaTimeInSeconds());
			Matrix finalM = tReverseM * rM * tM;

			// Transform the orbital points to a new orientation
			up = up * finalM;
			pos = pos * finalM;
			tar = tar * finalM;

			// Set the new orbital data to the camera
			activeCamera.SetOrbitPoints(up, tar, pos);
		}

		if (Input::Keyboard::GetKey(Input::Key::ArrowRight))
		{
			// Get orbital data from the camera
			activeCamera.GetOrbitPoints(up, tar, pos, upNorm, forwardNorm, rightNorm, activeCamera.GetOrbitDistance());

			// Calculate matrices needed to orbit
			Matrix tM(MatrixTransType::TRANS, tar);
			Matrix tReverseM(MatrixTransType::TRANS, -tar);
			Matrix rM(RotAxisAngleType::ROT_AXIS_ANGLE, upNorm, this->orbitSpeed * Time::GetDeltaTimeInSeconds());
			Matrix finalM = tReverseM * rM * tM;

			// Transform the orbital points to a new orientation
			up = up * finalM;
			pos = pos * finalM;
			tar = tar * finalM;

			// Set the new orbital data to the camera
			activeCamera.SetOrbitPoints(up, tar, pos);
		}

		if (Input::Keyboard::GetKey(Input::Key::ArrowLeft))
		{
			// Get orbital data from the camera
			activeCamera.GetOrbitPoints(up, tar, pos, upNorm, forwardNorm, rightNorm, activeCamera.GetOrbitDistance());

			// Calculate matrices needed to orbit
			Matrix tM(MatrixTransType::TRANS, tar);
			Matrix tReverseM(MatrixTransType::TRANS, -tar);
			Matrix rM(RotAxisAngleType::ROT_AXIS_ANGLE, upNorm, -this->orbitSpeed * Time::GetDeltaTimeInSeconds());
			Matrix finalM = tReverseM * rM * tM;

			// Transform the orbital points to a new orientation
			up = up * finalM;
			pos = pos * finalM;
			tar = tar * finalM;

			// Set the new orbital data to the camera
			activeCamera.SetOrbitPoints(up, tar, pos);
		}

		if (Input::Keyboard::GetKey(Input::Key::A))
		{
			// Get orbital data from the camera
			activeCamera.GetOrbitPoints(up, tar, pos, upNorm, forwardNorm, rightNorm, activeCamera.GetOrbitDistance());

			// Calculate matrices needed to orbit
			Matrix tM(MatrixTransType::TRANS, tar);
			Matrix tReverseM(MatrixTransType::TRANS, -tar);
			Matrix rM(RotAxisAngleType::ROT_AXIS_ANGLE, forwardNorm, -this->orbitSpeed * Time::GetDeltaTimeInSeconds());
			Matrix finalM = tReverseM * rM * tM;

			// Transform the orbital points to a new orientation
			up = up * finalM;
			pos = pos * finalM;
			//tar = tar * finalM;

			// Set the new orbital data to the camera
			activeCamera.SetOrbitPoints(up, tar, pos);
		}

		if (Input::Keyboard::GetKey(Input::Key::D))
		{
			// Get orbital data from the camera
			activeCamera.GetOrbitPoints(up, tar, pos, upNorm, forwardNorm, rightNorm, activeCamera.GetOrbitDistance());

			// Calculate matrices needed to orbit
			Matrix tM(MatrixTransType::TRANS, tar);
			Matrix tReverseM(MatrixTransType::TRANS, -tar);
			Matrix rM(RotAxisAngleType::ROT_AXIS_ANGLE, forwardNorm, this->orbitSpeed * Time::GetDeltaTimeInSeconds());
			Matrix finalM = tReverseM * rM * tM;

			// Transform the orbital points to a new orientation
			up = up * finalM;
			pos = pos * finalM;
			//tar = tar * finalM;

			// Set the new orbital data to the camera
			activeCamera.SetOrbitPoints(up, tar, pos);
		}
	}



}