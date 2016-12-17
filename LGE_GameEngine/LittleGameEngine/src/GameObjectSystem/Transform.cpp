#include "Transform.h"
#include <cassert>
#include <cmath>

namespace lge
{
	Transform::Transform() :
		position(),
		eulerAngles(),
		scale(1.0f),
		forward(0.0f, 0.0f, 1.0f),
		right(1.0f, 0.0f, 0.0f),
		up(0.0f, 1.0f, 0.0f),
		modelMatrix(new Matrix(IDENTITY))
	{
	}

	Transform::~Transform()
	{
		assert(this->modelMatrix != nullptr);
		delete this->modelMatrix;
	}


	Transform& Transform::operator=(const Transform& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		this->position = rhs.position;
		this->eulerAngles = rhs.eulerAngles;
		this->scale = rhs.scale;

		this->RecalulateDirections();

		*(this->modelMatrix) = *(rhs.modelMatrix);

		return *this;
	}


	void Transform::SetPosition(const Vect& newPosition)
	{
		this->position = newPosition;
	}

	void Transform::SetPosition(const float x, const float y, const float z)
	{
		this->position.set(x, y, z);
	}


	void Transform::SetEulerAngles(const Vect& newEulers)
	{
		this->eulerAngles = newEulers;

		this->RecalulateDirections();
	}

	void Transform::SetEulerAngles(const float xAngle, const float yAngle, const float zAngle)
	{
		this->eulerAngles.set(xAngle, yAngle, zAngle);

		this->RecalulateDirections();
	}

	// Change the current rotation
	void Transform::SetEulerAngles(const Quat& newRotation)
	{
		this->eulerAngles = newRotation.convertToEulerAngles();

		this->RecalulateDirections();
	}


	void Transform::SetScale(const Vect& newScale)
	{
		this->scale = newScale;
	}

	void Transform::SetScale(const float xScale, const float yScale, const float zScale)
	{
		this->scale.set(xScale, yScale, zScale);
	}

	// Sets a new position and orientaton based off the LookAt algorithm
	void Transform::SetLookAt(const Vect& newPosition, const Vect& newUp, const Vect& newTarget)
	{
		// Set position
		this->position = newPosition;


		// Set orientation directions 

		// Point out of the screen into your EYE (Keenan's words, not mine)
		this->forward = newPosition - newTarget;
		this->forward.norm();

		// Clean up the vectors (Right hand rule)
		this->right = newUp.cross(this->forward);
		this->right.norm();

		this->up = this->forward.cross(this->right);
		this->up.norm();


		// Set Euler Angles

		// Get an orientation matrix from the new directions
		const Matrix orientM(RotOrientType::ROT_ORIENT, this->forward, this->up);

		// Calculate the euler angles from the new orientation matrix
		this->eulerAngles.x() = atan2f(orientM.m9(), orientM.m10());
		this->eulerAngles.y() = atan2f(-orientM.m8(),
									   sqrtf((orientM.m9() * orientM.m9()) + (orientM.m10() * orientM.m10()))
		);
		this->eulerAngles.z() = atan2f(orientM.m4(), orientM.m0());
	}



	const Vect Transform::GetPositionCopy() const
	{
		return this->position;
	}

	const Vect Transform::GetEulerAnglesCopy() const
	{
		return this->eulerAngles;
	}

	const Vect Transform::GetScaleCopy() const
	{
		return this->scale;
	}



	const Vect& Transform::GetPosition() const
	{
		return this->position;
	}

	const Vect& Transform::GetEulerAngles() const
	{
		return this->eulerAngles;
	}

	const Vect& Transform::GetScale() const
	{
		return this->scale;
	}



	const Vect& Transform::GetForwardDirection() const
	{
		return this->forward;
	}

	const Vect& Transform::GetRightDirection() const
	{
		return this->right;
	}

	const Vect& Transform::GetUpDirection() const
	{
		return this->up;
	}



	void Transform::CalculateModelMatrix()
	{
		// Order: S * R * T

		/*return Matrix(
			Matrix(SCALE, this->scale) *
			Matrix(ROT_Z, this->eulerAngles.z()) *
			Matrix(ROT_Y, this->eulerAngles.y()) *
			Matrix(ROT_X, this->eulerAngles.x()) *
			Matrix(TRANS, this->position)
		);*/

		assert(this->modelMatrix != nullptr);
		/**(this->modelMatrix) =  Matrix(SCALE, this->scale) *
								Matrix(ROT_Z, this->eulerAngles.z()) *
								Matrix(ROT_Y, this->eulerAngles.y()) *
								Matrix(ROT_X, this->eulerAngles.x()) *
								Matrix(TRANS, this->position);*/
		*(this->modelMatrix) = Matrix(SCALE, this->scale) *
			Matrix(Quat(Rot3AxisType::ROT_XYZ, this->eulerAngles.x(), this->eulerAngles.y(), this->eulerAngles.z())) *
			Matrix(TRANS, this->position);
	}


	// Get the model matrix calculated once at the end of each frame.
	// Does not do any calculations; use GenerateModelMatrix() for that
	const Matrix& Transform::GetModelMatrix() const
	{
		return *(this->modelMatrix);
	}


	// Only to be used by CameraTransformAdapter!
	void Transform::InvertForward()
	{
		this->forward *= -1.0f;
	}




	//
	// Private Routines
	//

	// Recalculate the orientation vectors (usually done after changing the rotation)
	void Transform::RecalulateDirections()
	{
		const Matrix sumRotations = Matrix(ROT_Z, this->eulerAngles.z()) * Matrix(ROT_Y, this->eulerAngles.y()) * Matrix(ROT_X, this->eulerAngles.x());

		this->forward = Vect(0.0f, 0.0f, 1.0f) * sumRotations;
		this->right = Vect(1.0f, 0.0f, 0.0f) * sumRotations;
		this->up = Vect(0.0f, 1.0f, 0.0f) * sumRotations;
	}
}
