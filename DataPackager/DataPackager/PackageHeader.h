#ifndef H_LGE_PGK_HDR
#define H_LGE_PGK_HDR

#define LGE_HDR_STR_SIZE 20
#define PACKAGE_NAME_SIZE LGE_HDR_STR_SIZE
#define PACKAGE_VERSION_SIZE LGE_HDR_STR_SIZE

// The package header prefixed onto the package of multiple LGE files
struct PackageHeader
{
	char packageName[PACKAGE_NAME_SIZE];
	char versionString[PACKAGE_VERSION_SIZE];
	int numChunks;
	int totalSize; // size of file (without package	header)


	// Ctor
	PackageHeader();

	// Setter for the package name (string copy)
	void SetPackageName(const char* const newName, const size_t strSize);

	// Setter for the version info (string copy)
	void SetVersionInfo(const char* const newVersion, const size_t strSize);

	// Process the command line arguments to get the name and version
	void ProcessArgs(const char* const versionStr, const char* const nameStr);
};

#endif