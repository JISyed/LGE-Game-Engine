#ifndef LGE_ENUM_TEXTURE_UNIT_H
#define LGE_ENUM_TEXTURE_UNIT_H

namespace lge
{
	// Represent all the texture units than OpenGL allows.
	// In other words, the ability to use multiple textures in one shader.
	// Each of these corresponds to a respective GL_TEXTURE{N}
	enum class TextureUnit : unsigned char
	{
		u0 = 0,
		u1 = 1,
		u2 = 2,
		u3 = 3,
		u4 = 4,
		u5 = 5,
		u6 = 6,
		u7 = 7,
		u8 = 8,
		u9 = 9,
		u10 = 10,
		u11 = 11,
		u12 = 12,
		u13 = 13,
		u14 = 14,
		u15 = 15,
		u16 = 16,
		u17 = 17,
		u18 = 18,
		u19 = 19,
		u20 = 20,
		u21 = 21,
		u22 = 22,
		u23 = 23,
		u24 = 24,
		u25 = 25,
		u26 = 26,
		u27 = 27,
		u28 = 28,
		u29 = 29,
		u30 = 30,
		u31 = 31,
	};
}
#endif