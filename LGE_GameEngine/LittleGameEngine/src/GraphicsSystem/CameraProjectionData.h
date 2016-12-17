#ifndef LGE_CAMERA_PROJECTION_DATA_H
#define LGE_CAMERA_PROJECTION_DATA_H
#include "MathEngine.h"
#include "..\CollisionSystem\BoundingSphere.h"

namespace lge
{
	// Struct required to calculate the camera frustum in world space (for collisions)
	class CameraProjectionData : public Align16
	{
	public:
		void calcFrustumVerts();
		void calcFrustumCollisionNormals();
		void setOrientAndPosition(const Vect &inUp, const Vect &inLookAt, const Vect &inPos);
		void calcPlaneHeightWidth();
		bool CameraProjectionData::checkCollisionWithFrustrum(const BoundingSphere& sphere);

		// camera unit vectors (up, dir, right)
		Vect	vUp;
		Vect	vDir;
		Vect	vRight;  // derived by up and dir
		Vect	vPos;

		// world space coords for viewing frustum
		Vect	nearTopLeft;
		Vect	nearTopRight;
		Vect	nearBottomLeft;
		Vect	nearBottomRight;

		Vect	farTopLeft;
		Vect	farTopRight;
		Vect	farBottomLeft;
		Vect	farBottomRight;

		// Normals of the frustum
		Vect	frontNorm;
		Vect	backNorm;
		Vect	rightNorm;

		Vect	leftNorm;
		Vect	topNorm;
		Vect	bottomNorm;

		// -------------------------------------------------------
		// unaligned data below this point:
		// -------------------------------------------------------

		// Define the frustum inputs
		float	nearDist;
		float	farDist;
		float	fovy;
		float	aspectRatio;

		// Screen size in world space
		float	near_height;
		float	near_width;
		float	far_height;
		float	far_width;
	};
}

#endif