#include "PackageHeader.h"
namespace lge
{
	PackageHeader::PackageHeader()
	{
		this->packageName[LGE_PACKAGE_NAME_SIZE - 1] = '\0';
		this->versionString[LGE_PACKAGE_VERSION_SIZE - 1] = '\0';
	}


}