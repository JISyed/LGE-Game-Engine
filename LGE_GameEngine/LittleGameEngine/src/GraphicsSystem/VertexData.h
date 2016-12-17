#ifndef H_LGE_VERTEX_DATA_STRUCT
#define H_LGE_VERTEX_DATA_STRUCT
namespace lge
{
	// Represents all data that composes a vertex
	struct VertexData
	{
		float x;	// X position
		float y;	// Y postion
		float z;	// Z position
		float u;	// Horizontal texture coordinate
		float v;	// Vertical texture coordinate
		float nx;	// Vertex normal (X component)
		float ny;	// Vertex normal (Y component)
		float nz;	// Vertex normal (Z component)
		float w0;	// The percentage influence of the first bone (skinning weight)
		float w1;	// The percentage influence of the second bone (skinning weight)
		float w2;	// The percentage influence of the third bone (skinning weight)
		float w3;	// The percentage influence of the fourth bone (skinning weight)
		unsigned int b0;	// The index of the first bone (for skinning)
		unsigned int b1;	// The index of the second bone (for skinning)
		unsigned int b2;	// The index of the third bone (for skinning)
		unsigned int b3;	// The index of the fourth bone (for skinning)
	};
}
#endif