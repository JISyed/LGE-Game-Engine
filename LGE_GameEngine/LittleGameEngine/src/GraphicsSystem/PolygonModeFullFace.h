#ifndef LGE_POLYGON_MODE_FULL_FACE_H
#define LGE_POLYGON_MODE_FULL_FACE_H

#include "PolygonMode.h"

namespace lge
{
	// Polygon-rendering mode that draws the full face of a mesh without back faces
	class PolygonModeFullFace : public PolygonMode
	{
	public:

		//
		// Ctor / Dtor
		//

		PolygonModeFullFace();
		virtual ~PolygonModeFullFace();


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
		PolygonModeFullFace(const PolygonModeFullFace& other) = delete;

		// No copy assignment
		PolygonModeFullFace& operator=(const PolygonModeFullFace& other) = delete;

		// No move ctor
		PolygonModeFullFace(PolygonModeFullFace&& other) = delete;

		// No move assignment
		PolygonModeFullFace& operator=(PolygonModeFullFace&& other) = delete;
	};
}
#endif