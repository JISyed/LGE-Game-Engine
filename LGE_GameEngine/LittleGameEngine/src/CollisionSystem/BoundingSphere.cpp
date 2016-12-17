#include "BoundingSphere.h"

namespace lge
{

	BoundingSphere::BoundingSphere() :
		center(),
		radius(1.0f)
	{
	}

	BoundingSphere::BoundingSphere(const Vect& newCenter, const float newRadius) :
		center(newCenter),
		radius(newRadius)
	{
	}

	BoundingSphere::BoundingSphere(const BoundingSphere& other) :
		center(other.center),
		radius(other.radius)
	{
	}

	BoundingSphere::~BoundingSphere()
	{
	}

	BoundingSphere& BoundingSphere::operator=(const BoundingSphere& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		this->center = rhs.center;
		this->radius = rhs.radius;

		return *this;
	}


	const Vect BoundingSphere::GetCenter() const
	{
		return this->center;
	}

	const float BoundingSphere::GetRadius() const
	{
		return this->radius;
	}

	void BoundingSphere::SetCenter(const Vect& newCenter)
	{
		this->center = newCenter;
	}

	void BoundingSphere::SetRadius(const float newRadius)
	{
		this->radius = newRadius;
	}
}