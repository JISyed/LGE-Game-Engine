#ifndef LGE_TRANSFORM_H
#define LGE_TRANSFORM_H

#include "MathEngine.h"

namespace lge
{
	// Represent the world-space transform of an object
	class Transform final : public Align16
	{
	public:

		//
		// Big Four
		//

		Transform();
		~Transform();
		Transform& operator=(const Transform& rhs);


		//
		// Setters
		//

		// Set a new position
		void SetPosition(const Vect& newPosition);
		// Set a new position
		void SetPosition(const float x, const float y, const float z);

		// Change the current rotation. In radians
		void SetEulerAngles(const Vect& newEulers);
		// Change the current rotation. In radians
		void SetEulerAngles(const float xAngle, const float yAngle, const float zAngle);
		// Change the current rotation
		void SetEulerAngles(const Quat& newRotation);

		// Change the current scaling (x1 is default size)
		void SetScale(const Vect& newScale);
		// Change the current scaling (x1 is defualt size)
		void SetScale(const float xScale, const float yScale, const float zScale);

		// Sets a new position and orientaton based off the LookAt algorithm
		void SetLookAt(const Vect& newPosition, const Vect& newUp, const Vect& newTarget);


		//
		// Getters
		//

		// Get a copy of the position
		const Vect GetPositionCopy() const;
		// Get a copy of the rotations
		const Vect GetEulerAnglesCopy() const;
		// Get a copy of the scalings
		const Vect GetScaleCopy() const;

		// Get the position (read-only)
		const Vect& GetPosition() const;
		// Get the rotations (read-only)
		const Vect& GetEulerAngles() const;
		// Get the scalings (read-only)
		const Vect& GetScale() const;

		// Get the current forward orientation (read-only)
		const Vect& GetForwardDirection() const;
		// Get the current right orientation (read-only)
		const Vect& GetRightDirection() const;
		// Get the current up orientation (read-only)
		const Vect& GetUpDirection() const;




		//
		// Methods
		//

		// Only GameObject should ever be calling this, once per object per frame.
		// Computes a model matrix for the current transform data. Should call in draw loop
		void CalculateModelMatrix();

		// Get the model matrix calculated once at the end of each frame.
		// Does not do any calculations; use GenerateModelMatrix() for that
		const Matrix& GetModelMatrix() const;

		// Only to be used by CameraTransformAdapter!
		// Invert the forward orientation
		void InvertForward();




	private:

		//
		// Data
		//

		Vect position;
		Vect eulerAngles;
		Vect scale;
		Vect forward;
		Vect right;
		Vect up;
		Matrix* modelMatrix;


		//
		// Private Routines
		//

		// Recalculate the orientation vectors (usually done after changing the rotation)
		void RecalulateDirections();




		//
		// Deleted Methods
		//

		// No copy ctor
		Transform(const Transform& other) = delete;

		// No move ctor
		Transform(Transform&& other) = delete;

		// No move assignment
		Transform& operator=(Transform&& other) = delete;
	};

	
}

#endif