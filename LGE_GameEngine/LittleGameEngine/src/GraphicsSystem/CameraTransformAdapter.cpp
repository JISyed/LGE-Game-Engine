#include "CameraTransformAdapter.h"
#include <cassert>

namespace lge
{
	CameraTransformAdapter::CameraTransformAdapter() :
		theTransform()
	{
		this->theTransform.SetEulerAngles(0.0f, 0.0f, 0.0f);
		this->theTransform.InvertForward();
	}

	CameraTransformAdapter::~CameraTransformAdapter()
	{
	}

	CameraTransformAdapter& CameraTransformAdapter::operator=(const CameraTransformAdapter& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		this->theTransform = rhs.theTransform;

		return *this;
	}




	const Vect& CameraTransformAdapter::GetPosition() const
	{
		return this->theTransform.GetPosition();
	}

	const Vect& CameraTransformAdapter::GetEulerAngles() const
	{
		return this->theTransform.GetEulerAngles();
	}

	const Vect& CameraTransformAdapter::GetForwardDirection() const
	{
		return this->theTransform.GetForwardDirection();
	}

	const Vect& CameraTransformAdapter::GetRightDirection() const
	{
		return this->theTransform.GetRightDirection();
	}

	const Vect& CameraTransformAdapter::GetUpDirection() const
	{
		return this->theTransform.GetUpDirection();
	}




	void CameraTransformAdapter::SetPosition(const Vect& newPosition)
	{
		this->theTransform.SetPosition(newPosition);
	}

	// In radians
	void CameraTransformAdapter::SetEulerAngles(const Vect& newEulers)
	{
		this->theTransform.SetEulerAngles(newEulers);
		this->theTransform.InvertForward();
	}

	// Sets a new position and orientaton based off the LookAt algorithm
	void CameraTransformAdapter::SetLookAt(const Vect& newPosition, const Vect& newUp, const Vect& newTarget)
	{
		this->theTransform.SetLookAt(newPosition, newUp, newTarget);
		this->theTransform.SetEulerAngles(-this->theTransform.GetEulerAngles());
		this->theTransform.InvertForward();
	}


	const Matrix CameraTransformAdapter::GenerateViewMatrix() const
	{
		const Vect& right = this->theTransform.GetRightDirection();
		const Vect& up = this->theTransform.GetUpDirection();
		const Vect& camPos = this->theTransform.GetPosition();
		Vect dir = this->theTransform.GetForwardDirection() *-1.0f;


		Matrix view(IDENTITY);
		view.set(MatrixRowType::ROW_0, Vect(right.x(), up.x(), dir.x(), 0.0f));
		view.set(MatrixRowType::ROW_1, Vect(right.y(), up.y(), dir.y(), 0.0f));
		view.set(MatrixRowType::ROW_2, Vect(right.z(), up.z(), dir.z(), 0.0f));
		view.set(MatrixRowType::ROW_3, Vect(-camPos.dot(right), -camPos.dot(up), -camPos.dot(dir), 1.0f));

		return view;
	}


}