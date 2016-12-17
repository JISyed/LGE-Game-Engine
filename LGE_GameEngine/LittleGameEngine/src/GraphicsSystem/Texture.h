#ifndef LGE_TEXTURE_H
#define LGE_TEXTURE_H

#include <cassert>
#include "GL\gl3w.h"
#include "..\EngineUtilities\IdGenerator.h"
#include "enumTextureUnit.h"
#include "UniformNameHelper.h"
#include "ImageBuffer.h"
#include "..\UnpackagerSystem\ResourceUnpacker.h"

namespace lge
{

	// TEMP: Find a better way to dynmically name textures
	enum class TextureName : unsigned int
	{
		Duckweed,
		DuckweedUp,
		DuckweedFlip,
		MarioGround,
		Rocks,
		ExampleNormalMap,

		SpaceFrigate,
		Astroboy,
		BuggyDiffuse,
		WarbearBrown,
		WarbearPolar,
		Default,
		TeddyBear
	};



	/////////////////////////////////////////
	//
	// Enums
	//
	/////////////////////////////////////////

	// Indicates the purpose of the texture. Add more if needed
	enum class TextureMapType : unsigned char
	{
		Color,
		Normal
	};

	// Indicate the dimensionality of the texture (2D, 3D, etc)
	enum class TextureTargetType : unsigned short
	{
		Tex2D = GL_TEXTURE_2D,
		//CubeMap = GL_TEXTURE_CUBE_MAP
	};

	// Determines how to handle texel wrapping outside the texture's coordinate range
	enum class TextureWrapType : unsigned short
	{
		Repeat = GL_REPEAT,
		MirroredRepeat = GL_MIRRORED_REPEAT,
		EdgeClamp = GL_CLAMP_TO_EDGE,
		BorderClamp = GL_CLAMP_TO_BORDER
	};

	// Indicates how texels should be blended up-close or far-away
	enum class TextureFilterType : unsigned char
	{
		Point,
		PointDistanceBlend,
		Bilinear,
		Trilinear
	};




	/////////////////////////////////////////
	//
	// Class Texture
	//
	/////////////////////////////////////////

	// Represents an image that can be sent to the GPU and sampled on every pixel
	class Texture
	{
	public:

		//
		// Ctor / Dtor
		//

		// Load a texture from file (TGA)
		Texture(const char* const texturePath, TextureMapType textureMapType, TextureName newName);
		// Load a texture from an image buffer
		Texture(const ImageBuffer& image, TextureMapType textureMapType, TextureName newName);
		// Load a texture from the resource package
		Texture(UseUnpacker_t useUnpacker, const char* const nameInPackage, TextureMapType textureMapType, TextureName newName);
		// Dtor
		~Texture();


		//
		// Methods
		//

		// Make this Texture the active texture for OpenGL rendering
		void MakeActive();



		//
		// Setters
		//

		// Set the texture filtering mode for this Texture
		void SetFiltering(TextureFilterType newFiltering);

		// Set the wrapping mode for this Texture
		void SetWrapping(TextureWrapType newWrapping);
		
		

		//
		// Getters
		//
		
		// Get the name of this Texture in the shader as a UniformName
		const UniformName GetNameInShader() const;

		// Get the mapping type of this texture (color, normal, etc.)
		const TextureMapType GetMapType() const;

		// Get the texture unit of this texture
		const TextureUnit GetTextureUnit() const;

		// Get the engine ID of this texture (this is not the OpenGL handle!)
		const unsigned int GetId() const;



	private:
		
		//
		// Data
		//

		GLuint openglHandle;
		const TextureTargetType targetType;
		const TextureUnit textureUnit;
		const TextureMapType mapType;
		TextureName name;
		bool errorTextureInUse;


		//
		// Static Data
		//

		static IdGenerator s_id_gen;



		//
		// Private Routines
		//

		void ActivateAndBind();






		//
		// Deleted Methods
		//

		// No copy assignment
		Texture& operator=(const Texture& other) = delete;

		// No copy ctor
		Texture(const Texture& other) = delete;

		// No default ctor
		Texture() = delete;

		// No move ctor
		Texture(Texture&& other) = delete;

		// No move assignment
		Texture& operator=(Texture&& other) = delete;





		//
		// Static Helpers
		//

		// Internal conversion from TextureMapType to UniformName.
		// Add more cases when adding to TextureMapType:
		static const UniformName MapTypeToName(TextureMapType textureMapType)
		{
			UniformName name = UniformName::ColorMapTexture2d;
			
			switch (textureMapType)
			{
				case TextureMapType::Color:
					name = UniformName::ColorMapTexture2d;
					break;
				case TextureMapType::Normal:
					name = UniformName::NormalMapTexture2d;
					break;
				default:
					// Need a new case to convert TextureMapType to UniformName
					assert(false);
					break;
			}

			return name;
		}


		// Internal conversion from TextureMapType to TextureUnit.
		// Add more cases when adding to TextureMapType:
		static const TextureUnit MapTypeToTextureUnit(TextureMapType textureMapType)
		{
			TextureUnit texUnit = TextureUnit::u0;

			switch (textureMapType)
			{
				case TextureMapType::Color:
					texUnit = TextureUnit::u0;
					break;
				case TextureMapType::Normal:
					texUnit = TextureUnit::u1;
					break;
				default:
					// Need a new case to convert TextureMapType to TextureUnit
					assert(false);
					break;
			}

			return texUnit;
		}



	};
}
#endif