#ifndef H_LGE_TRIANGLE_DATA_STRUCT
#define H_LGE_TRIANGLE_DATA_STRUCT
namespace lge
{
	// Represents every vertex that would compose of a renderable triangle
	struct TriangleData
	{
		unsigned int vertex0;	// The array index of the first vertex
		unsigned int vertex1;	// The array index of the second vertex
		unsigned int vertex2;	// The array index of the third vertex
	};
}
#endif