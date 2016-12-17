#ifndef LGE_POLYGON_MODE
#define LGE_POLYGON_MODE

namespace lge
{
	// Define how each polygon should render in OpenGL
	enum class PolygonModeType
	{
		// Render the full face of the polygon
		FullFace,

		// Render the polygon as a wireframe mesh
		Wireframe
	};




	// Inherit from this to define how polygons should render in OpenGL
	class PolygonMode
	{
	public:

		//
		// Ctor / Dtor
		//

		PolygonMode();
		virtual ~PolygonMode();


		//
		// Contracts
		//

		// Get the type of PolygonMode
		virtual PolygonModeType GetType() const = 0;
		
		// Setting states before rendering
		virtual void SetState() = 0;

		// Restoring states after rendering
		virtual void RestoreState() = 0;

	private:

	};
}
#endif