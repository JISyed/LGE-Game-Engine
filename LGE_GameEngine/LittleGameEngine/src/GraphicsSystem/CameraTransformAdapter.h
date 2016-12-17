#ifndef LGE_CAMERA_TRANSFORM_ADAPTER_H
#define LGE_CAMERA_TRANSFORM_ADAPTER_H

#include "MathEngine.h"
#include "..\GameObjectSystem\Transform.h"

namespace lge
{
	// Allows a Transform to be used by Camera, which it wasn't originally designed for
	class CameraTransformAdapter final : public Align16
	{
	public:

		//
		// Big Four
		//

		CameraTransformAdapter();
		~CameraTransformAdapter();
		CameraTransformAdapter& operator=(const CameraTransformAdapter& rhs);


		//
		// Getters
		//

		// Get the Camera's position
		const Vect& GetPosition() const;
		// Get the Camera's euler rotations. In radians
		const Vect& GetEulerAngles() const;
		// Get the Camera's forward direction
		const Vect& GetForwardDirection() const;
		// Get the Camera's right direction
		const Vect& GetRightDirection() const;
		// Get the Camera's up direction
		const Vect& GetUpDirection() const;


		//
		// Setters
		//

		// Set the position of the Camera
		void SetPosition(const Vect& newPosition);
		// Set the euler angles of the Camera
		void SetEulerAngles(const Vect& newEulers);
		// Sets a new position and orientaton based off the LookAt algorithm
		void SetLookAt(const Vect& newPosition, const Vect& newUp, const Vect& newTarget);


		//
		// Methods
		//

		// Generate a view matrix from the Camera's transform
		const Matrix GenerateViewMatrix() const;




	private:

		//
		// Data
		//

		Transform theTransform;




		//
		// Deleted Methods
		//

		// No copy constructor
		CameraTransformAdapter(const CameraTransformAdapter& other) = delete;

		// No move ctor
		CameraTransformAdapter(CameraTransformAdapter&& other) = delete;

		// No move assignment
		CameraTransformAdapter& operator=(CameraTransformAdapter&& other) = delete;
	};

	
}

#endif