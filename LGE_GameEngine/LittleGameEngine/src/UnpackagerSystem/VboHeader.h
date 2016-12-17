#ifndef H_LGE_PKG_VBO_HEADER
#define H_LGE_PKG_VBO_HEADER
namespace lge
{
	// Metadata for a Vertex Buffer Object, so that the Engine can process the vertices correctly
	struct VboHeader
	{
		int rawSizeInBytes;		// The total size in bytes (sizeOfElement * numberOfElements)
		int sizeOfElement;		// usually sizeof(float)
		int numberOfElement;	// number of floats in this VBO
	};
}
#endif