#ifndef LGE_BOUNDING_SPHERE_H
#define LGE_BOUNDING_SPHERE_H

#include "MathEngine.h"

namespace lge
{
	// Bounding Sphere used to define collision space in an object
	class BoundingSphere : public Align16
	{
	public:
		BoundingSphere();
		BoundingSphere(const Vect& newCenter, const float newRadius);
		BoundingSphere(const BoundingSphere& other);
		~BoundingSphere();

		// Overload
		BoundingSphere& operator=(const BoundingSphere& rhs);

		const Vect GetCenter() const;
		const float GetRadius() const;

		void SetCenter(const Vect& newCenter);
		void SetRadius(const float newRadius);

	private:
		Vect center;
		float radius;

	};
}
#endif