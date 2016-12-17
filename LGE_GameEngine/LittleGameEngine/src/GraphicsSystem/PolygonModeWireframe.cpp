#include "PolygonModeWireframe.h"
#include "GL\gl3w.h"

namespace lge
{
	PolygonModeWireframe::PolygonModeWireframe()
	{
	}

	// VIRTUAL
	PolygonModeWireframe::~PolygonModeWireframe()
	{
	}

	// VIRTUAL
	// Get the type of PolygonMode
	PolygonModeType PolygonModeWireframe::GetType() const
	{
		return PolygonModeType::Wireframe;
	}

	// VIRTUAL
	// Setting states before rendering
	void PolygonModeWireframe::SetState()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
	}

	// VIRTUAL
	// Restoring states after rendering
	void PolygonModeWireframe::RestoreState()
	{
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}