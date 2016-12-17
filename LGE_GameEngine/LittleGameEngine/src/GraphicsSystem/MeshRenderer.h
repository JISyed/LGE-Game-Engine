#ifndef LGE_MESH_RENDERER_H
#define LGE_MESH_RENDERER_H

#include "IRenderable.h"

namespace lge
{
	// Forward declares
	class Material;
	class Mesh;
	class Matrix;


	// Soley responsible for rendering a Mesh using a Material
	class MeshRenderer : public IRenderable
	{
	public:

		//
		// Ctor / Dtor
		//

		// Default ctor (do NOT call unless you are NullMeshRenderer)
		MeshRenderer();
		MeshRenderer(Material* const newMaterial, Mesh* const newMesh, const Matrix& gameObjectTransform);
		virtual ~MeshRenderer();




		//
		// Setters
		//

		// Set the model matrix used to position the Mesh
		void SetModelMatrix(const Matrix& gameObjectMatrix);

		// Change the Material used to render with
		void SetMaterial(Material * const newMaterial);

		// Change the Mesh to render
		void SetMesh(Mesh * const newMesh);



		//
		// Getters
		//

		// Get the model matrix
		const Matrix& GetModelMatrix() const;

		// Get the current matrial
		Material* const GetCurrentMaterial();

		// Get teh current mesh
		Mesh* const GetCurrentMesh();



	protected:

		//
		// Contracts
		//

		// Setting states in OpenGL
		virtual void SetState();

		// Sending data to the GPU if needed
		virtual void SetGpuData();

		// Actual draw call
		virtual void Render();

		// Restoring states back to prevent unexpected rendering behavior
		virtual void RestoreState();


		//
		// Private routines
		//

		// This needs to be overriden by NullMeshRenderer
		virtual void destructorProc();

		

	private:

		//
		// Data
		//

		Material* sharedMaterial;
		Mesh* sharedMesh;
		Matrix* modelMatrix;



		//
		// Deleted Methods
		//

		// No Default Ctor
		//MeshRenderer() = delete;

		// No copy ctor
		MeshRenderer(const MeshRenderer& other) = delete;

		// No copy assignment
		MeshRenderer& operator=(const MeshRenderer& other) = delete;

		// No move ctor
		MeshRenderer(MeshRenderer&& other) = delete;

		// No move assignment
		MeshRenderer& operator=(MeshRenderer&& other) = delete;

	};
}
#endif