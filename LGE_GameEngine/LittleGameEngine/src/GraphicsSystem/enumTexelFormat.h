#ifndef H_LGE_TEXEL_FORMAT
#define H_LGE_TEXEL_FORMAT
#include "GL\gl3w.h"
namespace lge
{
	// Describes the color data ordering of the texture element (texel)
	enum class TexelFormat : unsigned short
	{
		RGB,	// Most common/default format
		BGR,
		BGRA,
		RGBA
	};

	GLenum ConvertToOpenGL(const TexelFormat format);
}
#endif