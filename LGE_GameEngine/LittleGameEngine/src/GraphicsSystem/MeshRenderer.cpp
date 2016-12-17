#include "MeshRenderer.h"
#include "Camera.h"

#include <cassert>
#include "GL\gl3w.h"
#include "Mesh.h"
#include "MathEngine.h"
#include "Material.h"


namespace lge
{
	MeshRenderer::MeshRenderer() :
		sharedMaterial(nullptr),
		sharedMesh(nullptr)
	{
		this->modelMatrix = new Matrix(IDENTITY);
	}


	MeshRenderer::MeshRenderer(Material* const newMaterial, Mesh* const newMesh, const Matrix& gameObjectTransform) :
		sharedMaterial(newMaterial),
		sharedMesh(newMesh)
	{
		assert(newMaterial != nullptr);
		assert(newMesh != nullptr);
		this->modelMatrix = new Matrix(IDENTITY);
		*(this->modelMatrix) = gameObjectTransform;
	}

	// VIRTUAL
	// Dtor
	MeshRenderer::~MeshRenderer()
	{
		this->destructorProc();
	}




	void MeshRenderer::SetModelMatrix(const Matrix& gameObjectMatrix)
	{
		*(this->modelMatrix) = gameObjectMatrix;
	}

	void MeshRenderer::SetMaterial(Material * const newMaterial)
	{
		this->sharedMaterial = newMaterial;
	}

	void MeshRenderer::SetMesh(Mesh * const newMesh)
	{
		this->sharedMesh = newMesh;
	}




	// Get the model matrix
	const Matrix& MeshRenderer::GetModelMatrix() const
	{
		return *(this->modelMatrix);
	}

	// Get the current matrial
	Material* const MeshRenderer::GetCurrentMaterial()
	{
		return this->sharedMaterial;
	}

	// Get teh current mesh
	Mesh* const MeshRenderer::GetCurrentMesh()
	{
		return this->sharedMesh;
	}





	// VIRTUAL
	// Setting states in OpenGL
	void MeshRenderer::SetState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);

		this->sharedMaterial->SetPolygonRenderState();
	}

	// VIRTUAL
	// Sending data to the GPU if needed
	void MeshRenderer::SetGpuData()
	{
		// set the vao
		this->sharedMesh->MakeActiveMesh();

		// Setup the projection matrix
		this->sharedMaterial->SetUniform(UniformName::ProjectionMatrix, Camera::GetActiveCamera().GetProjection());

		// Get the view matrix
		this->sharedMaterial->SetUniform(UniformName::ViewMatrix, Camera::GetActiveCamera().GetView());

		// Set the model matrix
		this->sharedMaterial->SetUniform(UniformName::ModelMatrix, *(this->modelMatrix));


		// use this Material (and its shader), will automagiacally send uniforms into the shader and GPU
		this->sharedMaterial->MakeActive();

		
	}

	// VIRTUAL
	// Actual draw call
	void MeshRenderer::Render()
	{
		// Draw
		glDrawElements(GL_TRIANGLES, this->sharedMesh->GetNumberOfTriangles() * 3, GL_UNSIGNED_INT, 0);
	}

	// VIRTUAL
	// Restoring states back to prevent unexpected rendering behavior
	void MeshRenderer::RestoreState()
	{
		this->sharedMaterial->RestorePolygonRenderState();

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}


	// VIRTUAL
	// This needs to be overriden by NullMeshRenderer
	void MeshRenderer::destructorProc()
	{
		this->sharedMaterial = nullptr;
		this->sharedMesh = nullptr;
		if (this->modelMatrix != nullptr)
		{
			delete this->modelMatrix;
		}
	}

}