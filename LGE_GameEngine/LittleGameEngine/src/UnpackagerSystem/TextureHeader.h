#ifndef H_LGE_PKG_TEXTURE_HEADER
#define H_LGE_PKG_TEXTURE_HEADER
#include "..\GraphicsSystem\enumTexelFormat.h"
namespace lge
{
	// Contains metadata about the texture so that the engine can load it properly
	struct TextureHeader
	{
		int width;					// The width of the texture
		int height;					// The height of the texture
		int depth;					// Should only be 8, 24, or 32
		TexelFormat gpuFormat;		// The color format of the texture inside the GPU
		TexelFormat imageFormat;	// The color format of the texture when loaded from file
	};
}
#endif