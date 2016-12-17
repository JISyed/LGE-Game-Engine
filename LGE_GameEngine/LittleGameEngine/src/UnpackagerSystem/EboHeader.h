#ifndef H_LGE_PKG_EBO_HEADER
#define H_LGE_PKG_EBO_HEADER
namespace lge
{
	// Metadata for a Element Buffer Object, so that the Engine can process the triangle indices correctly
	struct EboHeader
	{
		int rawSizeInBytes;		// The total size in bytes (sizeOfElement * numberOfElements)
		int sizeOfElement;		// usually sizeof(int)
		int numberOfElement;	// number of ints in this EBO
	};
}
#endif