#ifndef LGE_CAMERA_CONTROLLER_H
#define LGE_CAMERA_CONTROLLER_H

namespace lge
{
	enum class CameraControlMode
	{
		FreeStrafe,
		Orbit
	};

	class CameraController
	{
	public:
		CameraController();
		~CameraController();

		// Will only initialize if it wasn't before
		void Init();

		// Run in the update loop to allow control of cameras
		void Update();

	private:

		float translationSpeed;
		float rotationSpeed;
		float orbitSpeed;
		int currCameraId;
		CameraControlMode ctrlMode;
		bool isInitialized;


		void UpdateMode();
		void UpdateMovement();
		void UpdateCameraSwitching();
		void UpdateOrbitalDistance();

		void MoveInFreeStrafe();
		void MoveInOrbit();

	};
}
#endif