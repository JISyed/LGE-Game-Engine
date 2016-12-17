#include "CameraProjectionData.h"
#include <cmath>

namespace lge
{
	void CameraProjectionData::calcFrustumVerts()
	{
		// Top Left corner and so forth.  In this form to see the pattern
		// Might be confusing (remember the picture) vDir goes from screen into your EYE
		// so distance from the eye is "negative" vDir
		this->nearTopLeft =     this->vPos - this->vDir * this->nearDist + this->vUp * this->near_height * 0.5f - this->vRight * this->near_width * 0.5f;
		this->nearTopRight =    this->vPos - this->vDir * this->nearDist + this->vUp * this->near_height * 0.5f + this->vRight * this->near_width * 0.5f;
		this->nearBottomLeft =  this->vPos - this->vDir * this->nearDist - this->vUp * this->near_height * 0.5f - this->vRight * this->near_width * 0.5f;
		this->nearBottomRight = this->vPos - this->vDir * this->nearDist - this->vUp * this->near_height * 0.5f + this->vRight * this->near_width * 0.5f;
		this->farTopLeft =      this->vPos - this->vDir * this->farDist  + this->vUp * this->far_height  * 0.5f - this->vRight * this->far_width  * 0.5f;
		this->farTopRight =     this->vPos - this->vDir * this->farDist  + this->vUp * this->far_height  * 0.5f + this->vRight * this->far_width  * 0.5f;
		this->farBottomLeft =   this->vPos - this->vDir * this->farDist  - this->vUp * this->far_height  * 0.5f - this->vRight * this->far_width  * 0.5f;
		this->farBottomRight =  this->vPos - this->vDir * this->farDist  - this->vUp * this->far_height  * 0.5f + this->vRight * this->far_width  * 0.5f;
	}

	void CameraProjectionData::calcFrustumCollisionNormals()
	{
		// Normals of the frustum around nearTopLeft
		Vect A = this->nearBottomLeft - this->nearTopLeft;
		Vect B = this->nearTopRight - this->nearTopLeft;
		Vect C = this->farTopLeft - this->nearTopLeft;

		this->frontNorm = A.cross(B);
		this->frontNorm.norm();

		this->leftNorm = C.cross(A);
		this->leftNorm.norm();

		this->topNorm = B.cross(C);
		this->topNorm.norm();

		// Normals of the frustum around farBottomRight
		A = this->farBottomLeft - this->farBottomRight;
		B = this->farTopRight - this->farBottomRight;
		C = this->nearBottomRight - this->farBottomRight;

		this->backNorm = A.cross(B);
		this->backNorm.norm();

		this->rightNorm = B.cross(C);
		this->rightNorm.norm();

		this->bottomNorm = C.cross(A);
		this->bottomNorm.norm();
	}

	void CameraProjectionData::setOrientAndPosition(const Vect &inUp, const Vect &inLookAt, const Vect &inPos)
	{
		// Remember the up, lookAt and right are unit, and are perpendicular.
		// Treat lookAt as king, find Right vect, then correct Up to insure perpendiculare.
		// Make sure that all vectors are unit vectors.

		//this->vLookAt = inLookAt;

		// Point out of the screen into your EYE
		this->vDir = inPos - inLookAt;
		this->vDir.norm();

		// Clean up the vectors (Right hand rule)
		this->vRight = inUp.cross(this->vDir);
		this->vRight.norm();

		this->vUp = this->vDir.cross(this->vRight);
		this->vUp.norm();

		this->vPos = inPos;
	}


	void CameraProjectionData::calcPlaneHeightWidth()
	{

		this->near_height = 2.0f * tan((this->fovy * MATH_PI / 180.0f) * .5f) * this->nearDist;
		this->near_width = this->near_height * this->aspectRatio;

		this->far_height = 2.0f * tan((this->fovy * MATH_PI / 180.0f) * .5f) * this->farDist;
		this->far_width = this->far_height * this->aspectRatio;
	}


	bool CameraProjectionData::checkCollisionWithFrustrum(const BoundingSphere& sphere)
	{
		bool isSphereInside = true;

		// The displacement between the center of the sphere and collision plane of the frustum
		Vect ctrToPln = sphere.GetCenter() - this->nearTopLeft;

		// Or's does early outs if its evaluated true early

		// Check one corner with frustum planes
		if ((ctrToPln.dot(this->topNorm) > sphere.GetRadius()) ||
			(ctrToPln.dot(this->leftNorm) > sphere.GetRadius()) ||
			(ctrToPln.dot(this->frontNorm) > sphere.GetRadius()) )
		{
			isSphereInside = false;
		}
		// Check opposite corner with frustum planes
		else
		{
			ctrToPln = sphere.GetCenter() - this->farBottomRight;
			if ((ctrToPln.dot(this->backNorm) > sphere.GetRadius()) ||
				(ctrToPln.dot(this->rightNorm) > sphere.GetRadius()) ||
				(ctrToPln.dot(this->bottomNorm) > sphere.GetRadius()))
			{
				isSphereInside = false;
			}
		}

		return isSphereInside;
	}
}