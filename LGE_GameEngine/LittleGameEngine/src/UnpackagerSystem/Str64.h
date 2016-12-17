#ifndef H_LGE_PKG_STRING_64
#define H_LGE_PKG_STRING_64
#include "..\AbstractDataTypes\CString.h"

namespace lge
{
	// A string with max length of 64. Used for name serailzation only
	struct Str64
	{
		char str[64];

		Str64()
		{
			for (int i = 0; i < 64; i++)
			{
				str[i] = '\0';
			}
		}

		CString ToCString()
		{
			this->str[63] = '\0';
			return CString(this->str);
		}
	};
}

#endif