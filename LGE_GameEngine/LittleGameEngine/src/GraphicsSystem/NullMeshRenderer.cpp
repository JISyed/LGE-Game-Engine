#include "NullMeshRenderer.h"
#include <cassert>

namespace lge
{
	NullMeshRenderer::NullMeshRenderer() :
		MeshRenderer()
	{
		this->SetMaterial(nullptr);
		this->SetMesh(nullptr);
	}

	// VIRTUAL
	NullMeshRenderer::~NullMeshRenderer()
	{
		this->destructorProc();
	}


	// VIRTUAL OVERRIDE
	// Setting states in OpenGL
	void NullMeshRenderer::SetState()
	{
		// Do nothing
	}

	// VIRTUAL OVERRIDE
	// Sending data to the GPU if needed
	void NullMeshRenderer::SetGpuData()
	{
		// Do nothing
	}

	// VIRTUAL OVERRIDE
	// Actual draw call
	void NullMeshRenderer::Render()
	{
		// Do nothing
	}

	// VIRTUAL OVERRIDE
	// Restoring states back to prevent unexpected rendering behavior
	void NullMeshRenderer::RestoreState()
	{
		// Do nothing
	}

	// VIRTUAL OVERRIDE
	// This needs to be overriden by NullMeshRenderer
	void NullMeshRenderer::destructorProc()
	{
		// Do nothing
	}


}