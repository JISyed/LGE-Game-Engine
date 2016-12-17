#ifndef LGE_CAMERA_H
#define LGE_CAMERA_H

#include "..\EngineUtilities\IdGenerator.h"
#include "CameraTransformAdapter.h"
#include "CameraProjectionData.h"
#include "MeshRenderer.h"
namespace lge
{
	// Foward declare
	class Vect;
	class Matrix;
	class GameObject;


	// Allows the viewing of a 3D scene onto a 2D screen
	class Camera
	{
	public:

		//
		// Ctor / Dtor
		//

		Camera();
		~Camera();


		//
		// Accessors
		//

		// Get the projection matrix of this camera
		const Matrix& GetProjection() const;

		// Get the view matrix of this camera
		const Matrix& GetView() const;

		// Set the projection matrix of this camera
		//void SetProjection(const Matrix& newProjection);
		void SetProjection(const float newYFieldOfView,
						   const float newAspectRatio,
						   const float newNearClip,
						   const float newFarClip);

		// Set the view matrix of this camera
		void SetView(const Matrix& newView);
		
		// Get the ID of this camera
		const unsigned int GetId() const;

		// Is this camera the currently active camera? There can only be 1 active camera
		const bool IsActive() const;

		// Get a mutable reference to the Camera's transform
		const CameraTransformAdapter& GetTransform();

		// Get the orientation points and vectors to compute orbiting movements
		void GetOrbitPoints(Vect& upPt, Vect& targetPt, Vect& positionPt, Vect& upDir, Vect& forwardDir, Vect& rightDir, const float targetDistance);

		// Set the orientation of the camera given the orientation points: up, target, and position
		void SetOrbitPoints(const Vect& upPt, const Vect& targetPt, const Vect& positionPt);

		// Get the orbit distance of this camera
		const float GetOrbitDistance() const;

		// Set the orbit distance of this camera
		void SetOrbitDistance(const float newDistance);

		// Get read only access to projection data
		const CameraProjectionData* const GetProjectionData() const;

		// Check if this Camera can render its fustrum
		//const bool CanRenderFustrum() const;

		// Set the fustrum mesh for this Camera (hard-coded to MeshName::CameraFustrum)
		//void SetFustrumMesh();

		// Explicity set a new position
		void SetPosition(const Vect& newPosition);

		// Explicity set euler angles
		void SetEulerAngles(const Vect& newEulerAngles);



		//
		// Methods
		//

		// Make this camera the active camera for rendering
		void MakeActive();

		// Update internal data for the camera
		void Update();

		// Draw the view fustrum of the camera, if it has one
		void DrawGizmos();

		// Returns true if this camera's frustum is colliding with a GameObject's bounding sphere
		const bool IsGameObjectInFrustum(const GameObject* const gameObject);



		//
		// Static Routines
		//

		// Get the camera currently marked as active (only one camera can be active at a time)
		static Camera& GetActiveCamera();

		// Calculate a projection matrix given projection properties.
		// "yFieldOfView" angle must be in degrees!
		static const Matrix CalculateProjection(const float newYFieldOfView, 
												const float newAspectRatio, 
												const float newNearClip, 
												const float newFarClip);


		// TODO: Make a Transform::LookAt() that calculates the correct Euler Angles!

		// Calculate the view matrix
		static const Matrix LookAt(const Vect& up, const Vect& targetPos, const Vect& camPos);




	private:

		//
		// Data
		//

		Matrix* projectionMatrix;
		Matrix* viewMatrix;
		CameraTransformAdapter* cameraTransform;
		CameraProjectionData* cameraProjection;
		MeshRenderer* orbitTargetRenderer;
		//MeshRenderer* fustrumRenderer;
		const unsigned int ID;
		float orbitDistance;
		bool isActive;


		//
		// Static Data
		//

		static Camera* s_currentActiveCamera;
		static IdGenerator s_idGen;



		//
		// Deleted Methods
		//

		// No copy ctor
		Camera(const Camera& other) = delete;

		// No copy assignment
		Camera& operator=(const Camera& other) = delete;

		// No move ctor
		Camera(Camera&& other) = delete;

		// No move assignment
		Camera& operator=(Camera&& other) = delete;
	};
}
#endif