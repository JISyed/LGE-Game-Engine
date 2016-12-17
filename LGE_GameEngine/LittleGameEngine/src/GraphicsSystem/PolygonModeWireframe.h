#ifndef LGE_POLYGON_MODE_WIREFRAME_H
#define LGE_POLYGON_MODE_WIREFRAME_H

#include "PolygonMode.h"

namespace lge
{
	// Polygon-rendering mode that draws the mesh as a wireframe with no culling
	class PolygonModeWireframe : public PolygonMode
	{
	public:

		//
		// Ctor / Dtor
		//

		PolygonModeWireframe();
		virtual ~PolygonModeWireframe();



		//
		// Contracts
		//

		// Get the type of PolygonMode
		virtual PolygonModeType GetType() const override;

		// Setting states before rendering
		virtual void SetState() override;

		// Restoring states after rendering
		virtual void RestoreState() override;



	private:

		//
		// Deleted Methods
		//

		// No copy ctor
		PolygonModeWireframe(const PolygonModeWireframe& other) = delete;

		// No copy assignment
		PolygonModeWireframe& operator=(const PolygonModeWireframe& other) = delete;

		// No move ctor
		PolygonModeWireframe(PolygonModeWireframe&& other) = delete;

		// No move assignment
		PolygonModeWireframe& operator=(PolygonModeWireframe&& other) = delete;
	};
}
#endif