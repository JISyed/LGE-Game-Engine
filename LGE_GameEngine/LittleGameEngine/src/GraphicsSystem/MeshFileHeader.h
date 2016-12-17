#ifndef LGE_MESH_FILE_HEADER_H
#define LGE_MESH_FILE_HEADER_H
namespace lge
{
	// File header for mesh data
	struct MeshFileHeader
	{
		unsigned int sizeOnBytes;
		unsigned int numVertices;
		unsigned int numTriangles;
	};
}
#endif