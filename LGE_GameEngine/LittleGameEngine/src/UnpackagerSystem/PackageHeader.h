#ifndef H_LGE_PKG_HEADER_STRUCT
#define H_LGE_PKG_HEADER_STRUCT
#define LGE_PKG_HDR_STR_SIZE 20
#define LGE_PACKAGE_NAME_SIZE LGE_PKG_HDR_STR_SIZE
#define LGE_PACKAGE_VERSION_SIZE LGE_PKG_HDR_STR_SIZE
namespace lge
{
	// The package header prefixed onto the package of multiple LGE files
	struct PackageHeader
	{
		char packageName[LGE_PACKAGE_NAME_SIZE];
		char versionString[LGE_PACKAGE_VERSION_SIZE];
		int numChunks;
		int totalSize; // size of file (without package	header)


		// Ctor
		PackageHeader();
	};
}
#endif