#ifndef LGE_MESH_RENDERER_NULL_H
#define LGE_MESH_RENDERER_NULL_H
#include "MeshRenderer.h"

namespace lge
{
	class NullMeshRenderer final : public MeshRenderer
	{
	public:
		NullMeshRenderer();
		virtual ~NullMeshRenderer();


	protected:

		//
		// Contracts
		//

		// Setting states in OpenGL
		virtual void SetState() override;

		// Sending data to the GPU if needed
		virtual void SetGpuData() override;

		// Actual draw call
		virtual void Render() override;

		// Restoring states back to prevent unexpected rendering behavior
		virtual void RestoreState() override;

		// This needs to be overriden by NullMeshRenderer
		virtual void destructorProc() override;


	private:

	};
}
#endif