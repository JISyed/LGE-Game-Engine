#include "PackageHeader.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "CliUtility.h"

PackageHeader::PackageHeader()
{
	memset(this->packageName, 0x0, PACKAGE_NAME_SIZE);
	this->packageName[PACKAGE_NAME_SIZE - 1] = '\0';

	memset(this->versionString, 0x0, PACKAGE_VERSION_SIZE);
	this->versionString[PACKAGE_VERSION_SIZE - 1] = '\0';

}


// Setter for the package name (string copy)
void PackageHeader::SetPackageName(const char* const newName, const size_t strSize)
{
	// Trying to get around dumb strncpy-is-unsafe warning
#if defined _WIN32
	strncpy_s(this->packageName, PACKAGE_NAME_SIZE, newName, strSize);
#else
	int toCopy = strSize > PACKAGE_NAME_SIZE ? PACKAGE_NAME_SIZE : strSize;
	strncpy(this->packageName, newName, toCopy);
#endif
	this->packageName[PACKAGE_NAME_SIZE - 1] = '\0';
}


// Setter for the version info (string copy)
void PackageHeader::SetVersionInfo(const char* const newVersion, const size_t strSize)
{
	// Trying to get around dumb strncpy-is-unsafe warning
#if defined _WIN32
	strncpy_s(this->versionString, PACKAGE_VERSION_SIZE, newVersion, strSize);
#else
	int toCopy = strSize > PACKAGE_VERSION_SIZE ? PACKAGE_VERSION_SIZE : strSize;
	strncpy(this->versionString, newVersion, toCopy);
#endif
	this->versionString[PACKAGE_VERSION_SIZE - 1] = '\0';
}


// Process the command line arguments to get the name and version
void PackageHeader::ProcessArgs(const char* const versionStr, const char* const nameStr)
{
	// Set the package name

	// +1 because strlen() doesn't include the null char at the end
	const size_t nameStrSize = strlen(nameStr) + 1;

	if (nameStrSize > PACKAGE_NAME_SIZE)
	{
		InvokeCliError(LGE_ERROR_NAME_TOO_BIG, nameStr);
	}

	this->SetPackageName(nameStr, nameStrSize);



	// Set the package version

	// +1 because strlen() doesn't include the null char at the end
	const size_t versionStrSize = strlen(versionStr) + 1;

	if (versionStrSize > PACKAGE_VERSION_SIZE)
	{
		InvokeCliError(LGE_ERROR_VERSION_STR_TOO_BIG, versionStr);
	}

	this->SetVersionInfo(versionStr, versionStrSize);
}

