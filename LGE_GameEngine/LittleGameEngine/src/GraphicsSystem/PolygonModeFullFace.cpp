#include "PolygonModeFullFace.h"
#include "GL\gl3w.h"

namespace lge
{
	PolygonModeFullFace::PolygonModeFullFace()
	{
	}

	// VIRTUAL
	PolygonModeFullFace::~PolygonModeFullFace()
	{
	}

	// VIRTUAL
	// Get the type of PolygonMode
	PolygonModeType PolygonModeFullFace::GetType() const
	{
		return PolygonModeType::FullFace;
	}

	// VIRTUAL
	// Setting states before rendering
	void PolygonModeFullFace::SetState()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
	}

	// VIRTUAL
	// Restoring states after rendering
	void PolygonModeFullFace::RestoreState()
	{
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}