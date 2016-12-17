#include "Camera.h"
#include <cassert>
#include <cmath>

#include "MathEngine.h"
#include "..\GameObjectSystem\GameObject.h"
#include "MaterialRegistry.h"
#include "MeshRegistry.h"

namespace lge
{

	//
	// Static Data
	//

	Camera* Camera::s_currentActiveCamera = nullptr;
	IdGenerator Camera::s_idGen;




	//
	// Methods
	//

	Camera::Camera() :
		ID(s_idGen.MakeNewId()),
		orbitDistance(5.0f),
		isActive(false)
	{
		this->projectionMatrix = new Matrix(IDENTITY);
		this->viewMatrix = new Matrix(IDENTITY);
		this->cameraTransform = new CameraTransformAdapter();
		this->cameraProjection = new CameraProjectionData();
		this->orbitTargetRenderer = new MeshRenderer(&MaterialRegistry::Find(MaterialName::CameraOrbitTarget), &MeshRegistry::Find(MeshName::Octahedron), *this->viewMatrix);
		//this->fustrumRenderer = nullptr;
	}

	Camera::~Camera()
	{
		delete this->projectionMatrix;
		delete this->viewMatrix;
		delete this->cameraTransform;
		delete this->cameraProjection;
		delete this->orbitTargetRenderer;

		/*if (this->fustrumRenderer != nullptr)
		{
			delete this->fustrumRenderer;
		}*/

		if (Camera::s_currentActiveCamera == this)
		{
			this->isActive = false;
			Camera::s_currentActiveCamera = nullptr;
		}
	}




	const Matrix& Camera::GetProjection() const
	{
		return *(this->projectionMatrix);
	}

	const Matrix& Camera::GetView() const
	{
		return *(this->viewMatrix);
	}


	void Camera::SetProjection(const float newYFieldOfView,
							   const float newAspectRatio,
							   const float newNearClip,
							   const float newFarClip)
	{
		this->cameraProjection->fovy = newYFieldOfView;
		this->cameraProjection->aspectRatio = newAspectRatio;
		this->cameraProjection->nearDist = newNearClip;
		this->cameraProjection->farDist = newFarClip;

		*(this->projectionMatrix) = Camera::CalculateProjection(newYFieldOfView,
																newAspectRatio,
																newNearClip,
																newFarClip);
	}


	void Camera::SetView(const Matrix& newView)
	{
		*(this->viewMatrix) = newView;
	}



	const unsigned int Camera::GetId() const
	{
		return this->ID;
	}


	const bool Camera::IsActive() const
	{
		return this->isActive;
	}




	const CameraTransformAdapter& Camera::GetTransform()
	{
		return *(this->cameraTransform);
	}



	// Make this camera the active camera for rendering
	void Camera::MakeActive()
	{
		if (Camera::s_currentActiveCamera != nullptr)
		{
			Camera::s_currentActiveCamera->isActive = false;
		}

		Camera::s_currentActiveCamera = this;
		this->isActive = true;

		this->Update();
	}



	// Update internal data for the camera
	void Camera::Update()
	{
		if (this->isActive)
		{
			// View Calculations

			// Calculate view matrix
			*(this->viewMatrix) = this->cameraTransform->GenerateViewMatrix();

			// Get camera world space data into projection calculations
			this->cameraProjection->vUp = this->cameraTransform->GetUpDirection();
			this->cameraProjection->vDir = -this->cameraTransform->GetForwardDirection();
			this->cameraProjection->vRight = this->cameraTransform->GetRightDirection();
			this->cameraProjection->vPos = this->cameraTransform->GetPosition();


			// Projection Calculations

			// First find the near height/width, far height/width
			this->cameraProjection->calcPlaneHeightWidth();

			// Find the frustum physical verts
			this->cameraProjection->calcFrustumVerts();

			// find the frustum collision normals
			this->cameraProjection->calcFrustumCollisionNormals();
		}
	}


	// Draw the view fustrum of the camera, if it has one
	void Camera::DrawGizmos()
	{
		static Mesh* sphereMesh = &MeshRegistry::Find(MeshName::BoundingSphere);

		if (this->isActive)
		{
			const Matrix targetTransform(MatrixTransType::TRANS, this->cameraTransform->GetPosition() + this->cameraTransform->GetForwardDirection() * this->orbitDistance);
			this->orbitTargetRenderer->SetModelMatrix( Matrix(MatrixScaleType::SCALE, 0.2f, 0.2f, 0.2f) * targetTransform );
			this->orbitTargetRenderer->Draw();
		}

		//if (this->CanRenderFustrum())
		//{
		//	Matrix fusPoint(IDENTITY);
		//	const Matrix invView = this->viewMatrix->getInv();
		//	this->fustrumRenderer->SetMesh(&MeshRegistry::Find(MeshName::CameraFustrum));
		//	this->fustrumRenderer->SetModelMatrix(invView);
		//	this->fustrumRenderer->Draw();

		//	// Draw the corners (for debugging)
		//	this->fustrumRenderer->SetMesh(sphereMesh);

		//	fusPoint = Matrix(TRANS, this->cameraProjection->farBottomLeft);
		//	this->fustrumRenderer->SetModelMatrix(fusPoint);
		//	this->fustrumRenderer->Draw();

		//	fusPoint = Matrix(TRANS, this->cameraProjection->farBottomRight);
		//	this->fustrumRenderer->SetModelMatrix(fusPoint);
		//	this->fustrumRenderer->Draw();

		//	fusPoint = Matrix(TRANS, this->cameraProjection->farTopLeft);
		//	this->fustrumRenderer->SetModelMatrix(fusPoint);
		//	this->fustrumRenderer->Draw();

		//	fusPoint = Matrix(TRANS, this->cameraProjection->farTopRight);
		//	this->fustrumRenderer->SetModelMatrix(fusPoint);
		//	this->fustrumRenderer->Draw();

		//	fusPoint = Matrix(TRANS, this->cameraProjection->nearBottomLeft);
		//	this->fustrumRenderer->SetModelMatrix(fusPoint);
		//	this->fustrumRenderer->Draw();

		//	fusPoint = Matrix(TRANS, this->cameraProjection->nearBottomRight);
		//	this->fustrumRenderer->SetModelMatrix(fusPoint);
		//	this->fustrumRenderer->Draw();

		//	fusPoint = Matrix(TRANS, this->cameraProjection->nearTopLeft);
		//	this->fustrumRenderer->SetModelMatrix(fusPoint);
		//	this->fustrumRenderer->Draw();

		//	fusPoint = Matrix(TRANS, this->cameraProjection->nearTopRight);
		//	this->fustrumRenderer->SetModelMatrix(fusPoint);
		//	this->fustrumRenderer->Draw();
		//}

	}


	// Returns true if this camera's frustum is colliding with a GameObject's bounding sphere
	const bool Camera::IsGameObjectInFrustum(const GameObject* const gameObject)
	{
		assert(gameObject != nullptr);
		return this->cameraProjection->checkCollisionWithFrustrum(gameObject->GetCorrectedBoundingSphere());
	}



	// Get the orientation points and vectors to compute orbiting movements
	void Camera::GetOrbitPoints(Vect& upPt, Vect& targetPt, Vect& positionPt, Vect& upDir, Vect& forwardDir, Vect& rightDir, const float targetDistance)
	{
		positionPt = this->cameraTransform->GetPosition();
		
		forwardDir = this->cameraTransform->GetForwardDirection();
		rightDir = this->cameraTransform->GetRightDirection();
		upDir = this->cameraTransform->GetUpDirection();

		targetPt = positionPt + (forwardDir * targetDistance);
		upPt = positionPt + upDir;
	}

	// Set the orientation of the camera given the orientation points: up, target, and position
	void Camera::SetOrbitPoints(const Vect& upPt, const Vect& targetPt, const Vect& positionPt)
	{
		const Vect upDir = upPt - positionPt;
		this->cameraTransform->SetLookAt(positionPt, upDir, targetPt);
	}

	// Get the orbit distance of this camera
	const float Camera::GetOrbitDistance() const
	{
		return this->orbitDistance;
	}

	// Set the orbit distance of this camera
	void Camera::SetOrbitDistance(const float newDistance)
	{
		this->orbitDistance = newDistance;
	}

	// Get read only access to projection data
	const CameraProjectionData* const Camera::GetProjectionData() const
	{
		return this->cameraProjection;
	}


	//// Check if this Camera can render its fustrum
	//const bool Camera::CanRenderFustrum() const
	//{
	//	return this->fustrumRenderer != nullptr;
	//}

	//// Set the fustrum mesh for this Camera (hard-coded to MeshName::CameraFustrum)
	//void Camera::SetFustrumMesh()
	//{
	//	if (this->CanRenderFustrum() == false)
	//	{
	//		this->fustrumRenderer = new MeshRenderer(&MaterialRegistry::Find(MaterialName::CameraFustrum), &MeshRegistry::Find(MeshName::CameraFustrum), *this->viewMatrix);
	//	}
	//}


	// Explicity set a new position
	void Camera::SetPosition(const Vect& newPosition)
	{
		this->cameraTransform->SetPosition(newPosition);
	}

	// Explicity set euler angles
	void Camera::SetEulerAngles(const Vect& newEulerAngles)
	{
		this->cameraTransform->SetEulerAngles(newEulerAngles);
	}





	// STATIC
	Camera& Camera::GetActiveCamera()
	{
		assert(Camera::s_currentActiveCamera != nullptr);
		return *(Camera::s_currentActiveCamera);
	}


	// STATIC
	// Calculate a projection matrix given projection properties.
	// "yFieldOfView" angle must be in degrees!
	const Matrix Camera::CalculateProjection(const float yFieldOfView,
											 const float aspectRatio,
											 const float nearClip,
											 const float farClip)
	{
		// Changing FOV or aspect-ratio (aspectRatio must change in all cameras)
		const float DegreeToRadians = 1.0f / lge::MATH_180_PI;
		const float cotangent = 1.0f / (tanf(DegreeToRadians * yFieldOfView * 0.5f));
		const float A = cotangent / aspectRatio;

		// Changing clip
		const float nearMinusFar = nearClip - farClip;
		const float B = (nearClip + farClip) / nearMinusFar;
		const float C = (2.0f * nearClip * farClip) / nearMinusFar;


		// Make projection matrix
		Matrix projection(ZERO);
		projection.m0() = A;
		projection.m5() = cotangent;
		projection.m10() = B;
		projection.m11() = -1.0f;
		projection.m14() = C;

		return projection;
	}

	// STATIC
	const Matrix Camera::LookAt(const Vect& up, const Vect& targetPos, const Vect& camPos)
	{
		// Remember the up, lookAt and right are unit, and are perpendicular.
		// Treat lookAt as king, find Right vect, then correct Up to insure perpendiculare.
		// Make sure that all vectors are unit vectors.

		//this->vLookAt = inLookAt;

		// Point out of the screen into your EYE
		Vect dir = camPos - targetPos;
		dir.norm();

		// Clean up the vectors (Right hand rule)
		// Assuming that up is already normalized!
		Vect right = up.cross(dir);


		// Assumes that up is already normalized!
		Vect actualUp = dir.cross(right);



		// This functions assumes the your vUp, vRight, vDir are still unit
		// And perpendicular to each other
		Matrix view(IDENTITY);
		view.set(MatrixRowType::ROW_0, Vect(right.x(), actualUp.x(), dir.x(), 0.0f));
		view.set(MatrixRowType::ROW_1, Vect(right.y(), actualUp.y(), dir.y(), 0.0f));
		view.set(MatrixRowType::ROW_2, Vect(right.z(), actualUp.z(), dir.z(), 0.0f));
		view.set(MatrixRowType::ROW_3, Vect(-camPos.dot(right), -camPos.dot(actualUp), -camPos.dot(dir), 1.0f));

		return view;

	}
}