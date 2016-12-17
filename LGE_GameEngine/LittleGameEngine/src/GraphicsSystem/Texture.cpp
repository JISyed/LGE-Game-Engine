#include "Texture.h"
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include "File.h"
#include "enumTexelFormat.h"

//
// C Protoypes
//

GLbyte* gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);



//
// C Static Data
//

// Define a texture when textures fail to load (GL_RGB)
static GLubyte errorTexture[] = {
	0x00, 0xFF, 0xFF,   0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0xFF,   0x00, 0x00, 0x00
};


namespace lge
{
	GLenum ConvertToOpenGL(const TexelFormat format)
	{
		GLenum oglFormat = GL_RGB;

		switch (format)
		{
			case TexelFormat::RGB:
				oglFormat = GL_RGB;
				break;
			case TexelFormat::BGR:
				oglFormat = GL_BGR;
				break;
			case TexelFormat::RGBA:
				oglFormat = GL_RGBA;
				break;
			case TexelFormat::BGRA:
				oglFormat = GL_BGRA;
				break;
			default:
				break;
		}

		return oglFormat;
	}
}



// ================================================================================
//
// Texture Class Begins
//
// ================================================================================
namespace lge
{
	//
	// Static Data
	//

	IdGenerator Texture::s_id_gen;



	//
	// Methods
	//

	// Load a texture from a file (TGA)
	Texture::Texture(const char* const texturePath, TextureMapType textureMapType, TextureName newName) :
		openglHandle(400000000u),
		targetType(TextureTargetType::Tex2D),
		textureUnit(Texture::MapTypeToTextureUnit(textureMapType)),
		mapType(textureMapType),
		//ID(s_id_gen.MakeNewId())
		name(newName),
		errorTextureInUse(false)
	{
		// Make the texture in OpenGL
		glGenTextures(1, &(this->openglHandle));
		
		
		// Make it the active texture (first by texture unit, then by target type)
		this->ActivateAndBind();

		const GLenum target = static_cast<GLenum>(this->targetType);

		{
			GLbyte *pBits = nullptr;
			int nWidth, nHeight, gpuFormat;
			GLenum imageFormat;

			// Read the texture bits
			pBits = gltReadTGABits(texturePath, &nWidth, &nHeight, &gpuFormat, &imageFormat);

			bool textureFailed = false;
			if (pBits == nullptr)
			{
				// Assert here in debug, but let this code run in release
				//assert(pBits != nullptr);

				// Load error texture ==========
				textureFailed = true;
				pBits = (GLbyte*) errorTexture;
				nWidth = 2;
				nHeight = 2;
				gpuFormat = GL_RGB;
				imageFormat = GL_RGB;
				this->SetWrapping(TextureWrapType::Repeat);
				this->SetFiltering(TextureFilterType::PointDistanceBlend);
				this->errorTextureInUse = true;
			}


			this->SetWrapping(TextureWrapType::EdgeClamp);

			this->SetFiltering(TextureFilterType::PointDistanceBlend);




			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


			glTexImage2D(target,				// Texture Target Type
						 0,						// Level of Detail
						 gpuFormat,				// Format to store in graphics card
						 nWidth,				// Image source width
						 nHeight,				// Image source height
						 0,						// Border
						 imageFormat,			// Image source format
						 GL_UNSIGNED_BYTE,		// Image source data type
						 pBits					// Image source
						 );

			if (pBits != nullptr && !textureFailed)
			{
				free(pBits);
			}
		}
		
		glGenerateMipmap(target);
	}


	// Load a texture from an image buffer. IMAGE_BUFFER
	Texture::Texture(const ImageBuffer& image, TextureMapType textureMapType, TextureName newName) :
		openglHandle(400000000u),
		targetType(TextureTargetType::Tex2D),
		textureUnit(Texture::MapTypeToTextureUnit(textureMapType)),
		mapType(textureMapType),
		//ID(s_id_gen.MakeNewId())
		name(newName),
		errorTextureInUse(false)
	{
		// Make the texture in OpenGL
		glGenTextures(1, &(this->openglHandle));


		// Make it the active texture (first by texture unit, then by target type)
		this->ActivateAndBind();

		const GLenum target = static_cast<GLenum>(this->targetType);

		{
			// Get the texture data from the image buffer
			const GLubyte* pBits = image.GetReadOnlyRawData();
			int nWidth = (int) image.GetWidth();
			int	nHeight = (int) image.GetHeight();
			int gpuFormat = GL_RGB;
			GLenum imageFormat = GL_RGB;

			
			bool textureFailed = false;
			if (pBits == nullptr || nWidth <= 0 || nHeight <= 0)
			{
				// Assert here in debug, but let this code run in release
				assert(pBits != nullptr);

				// Load error texture ==========
				textureFailed = true;
				pBits = (GLubyte*)errorTexture;
				nWidth = 2;
				nHeight = 2;
				gpuFormat = GL_RGB;
				imageFormat = GL_RGB;
				this->SetWrapping(TextureWrapType::Repeat);
				this->SetFiltering(TextureFilterType::PointDistanceBlend);
				this->errorTextureInUse = true;
			}


			this->SetWrapping(TextureWrapType::EdgeClamp);

			this->SetFiltering(TextureFilterType::PointDistanceBlend);




			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


			glTexImage2D(target,				// Texture Target Type
						 0,						// Level of Detail
						 gpuFormat,				// Format to store in graphics card
						 nWidth,				// Image source width
						 nHeight,				// Image source height
						 0,						// Border
						 imageFormat,			// Image source format
						 GL_UNSIGNED_BYTE,		// Image source data type
						 pBits					// Image source
						 );
		}

		glGenerateMipmap(target);
	}


	// Load a texture from the resource package. RESOURCE UNPACKER
	Texture::Texture(UseUnpacker_t useUnpacker, const char* const nameInPackage, TextureMapType textureMapType, TextureName newName) :
		openglHandle(400000000u),
		targetType(TextureTargetType::Tex2D),
		textureUnit(Texture::MapTypeToTextureUnit(textureMapType)),
		mapType(textureMapType),
		//ID(s_id_gen.MakeNewId())
		name(newName),
		errorTextureInUse(false)
	{
		// Make the texture in OpenGL
		useUnpacker;
		glGenTextures(1, &(this->openglHandle));


		// Make it the active texture (first by texture unit, then by target type)
		this->ActivateAndBind();

		const GLenum target = static_cast<GLenum>(this->targetType);

		{
			// Get the texture data from the Resource Package
			int gpuFormat = GL_RGB;
			GLenum imageFormat = GL_RGB;
			TextureHeader texHdr;
			GLubyte* pBits = nullptr;
			bool textureSuccess = true;
			
			// Load from resource package
			textureSuccess = ResourceUnpacker::ReadTexture(nameInPackage, texHdr, pBits);
			gpuFormat = ConvertToOpenGL(texHdr.gpuFormat);
			imageFormat = ConvertToOpenGL(texHdr.imageFormat);
			int nWidth = texHdr.width;
			int nHeight = texHdr.height;


			if (!textureSuccess || pBits == nullptr || nWidth <= 0 || nHeight <= 0)
			{
				// Assert here in debug, but let this code run in release
				assert(pBits != nullptr);
				assert(textureSuccess);

				// Load error texture ==========
				textureSuccess = true;
				pBits = (GLubyte*)errorTexture;
				nWidth = 2;
				nHeight = 2;
				gpuFormat = GL_RGB;
				imageFormat = GL_RGB;
				this->SetWrapping(TextureWrapType::Repeat);
				this->SetFiltering(TextureFilterType::PointDistanceBlend);
				this->errorTextureInUse = true;
			}


			this->SetWrapping(TextureWrapType::EdgeClamp);

			this->SetFiltering(TextureFilterType::PointDistanceBlend);




			//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


			glTexImage2D(target,				// Texture Target Type
						 0,						// Level of Detail
						 gpuFormat,				// Format to store in graphics card
						 nWidth,				// Image source width
						 nHeight,				// Image source height
						 0,						// Border
						 imageFormat,			// Image source format
						 GL_UNSIGNED_BYTE,		// Image source data type
						 pBits					// Image source
						 );
		}

		glGenerateMipmap(target);
	}



	// Dtor
	Texture::~Texture()
	{
		// Delete handler to texture
		glDeleteTextures(1, &(this->openglHandle));
	}





	void Texture::MakeActive()
	{
		this->ActivateAndBind();
	}

	
	void Texture::SetFiltering(TextureFilterType newFiltering)
	{
		if (this->errorTextureInUse)
		{
			// Error texture properties should not change
			return;
		}

		GLint minFilter = 0;
		GLint magFilter = 0;

		switch (newFiltering)
		{
			case TextureFilterType::Point:
				minFilter = GL_NEAREST_MIPMAP_NEAREST;
				magFilter = GL_NEAREST;
				break;
			case TextureFilterType::PointDistanceBlend:
				minFilter = GL_NEAREST_MIPMAP_LINEAR;
				magFilter = GL_NEAREST;
				break;
			case TextureFilterType::Bilinear:
				minFilter = GL_LINEAR_MIPMAP_NEAREST;
				magFilter = GL_LINEAR;
				break;
			case TextureFilterType::Trilinear:
				minFilter = GL_LINEAR_MIPMAP_LINEAR;
				magFilter = GL_LINEAR;
				break;
			default:
				// Unsupported TextureFilterType!
				assert(false);
				break;
		}

		this->ActivateAndBind();

		// Set filtering parameters
		const GLenum target = static_cast<GLenum>(this->targetType);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
	}



	void Texture::SetWrapping(TextureWrapType newWrapping)
	{
		if (this->errorTextureInUse)
		{
			// Error texture properties should not change
			return;
		}

		this->ActivateAndBind();

		const GLint wrapCode = static_cast<GLint>(newWrapping);
		const GLenum target = static_cast<GLenum>(this->targetType);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapCode);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapCode);
		glTexParameteri(target, GL_TEXTURE_WRAP_R, wrapCode);
	}



	const UniformName Texture::GetNameInShader() const
	{
		return Texture::MapTypeToName(this->mapType);
	}


	const TextureMapType Texture::GetMapType() const
	{
		return this->mapType;
	}


	const TextureUnit Texture::GetTextureUnit() const
	{
		return this->textureUnit;
	}



	// Get the engine ID of this texture (this is not the OpenGL handle!)
	const unsigned int Texture::GetId() const
	{
		//return this->ID;
		return static_cast<unsigned int>(this->name);
	}




	//
	// Private Methods
	//

	void Texture::ActivateAndBind()
	{
		glActiveTexture(GL_TEXTURE0 + static_cast<unsigned int>(this->textureUnit));
		glBindTexture(static_cast<GLenum>(this->targetType), this->openglHandle);
	}



}


// ================================================================================
//
// TGA Loading Voodoo
//
// ================================================================================

// Define targa header. This is only used locally.
#pragma pack(1)
typedef struct
{
	GLbyte	identsize;              // Size of ID field that follows header (0)
	GLbyte	colorMapType;           // 0 = None, 1 = paletted
	GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;  // First colour map entry
	unsigned short	colorMapLength; // Number of colors
	unsigned char 	colorMapBits;   // bits per palette entry
	unsigned short	xstart;         // image x origin
	unsigned short	ystart;         // image y origin
	unsigned short	width;          // width in pixels
	unsigned short	height;         // height in pixels
	GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
	GLbyte	descriptor;             // image descriptor
} TGAHEADER;
#pragma pack(8)

/////////////////////////////////////////
// Flip the image vertically
GLbyte* jisFlipTarga(GLint w, GLint h, short pixelDepth, size_t pixelSize, GLbyte* imageData)
{
	unsigned long imageSize = w * h * pixelDepth * pixelSize;

	GLbyte* flippedData = (GLbyte*)malloc(imageSize);
	assert(flippedData != (GLbyte*)0);

	// Algorithm taken from SFML ( sf::Image::flipVertically() )
	const size_t rowSize = w * pixelDepth * pixelSize;
	GLbyte* topSource = imageData;
	GLbyte* bottomSource = imageData + imageSize - rowSize;

	GLbyte* topDestination = flippedData;
	GLbyte* bottomDestination = flippedData + imageSize - rowSize;

	for (int y = 0; y < (h / 2); y++)
	{
		// Swap
		memcpy(bottomDestination, topSource, rowSize);
		memcpy(topDestination, bottomSource, rowSize);

		// Move pointers
		topSource += rowSize;
		bottomSource -= rowSize;
		topDestination += rowSize;
		bottomDestination -= rowSize;
	}

	free(imageData);
	return flippedData;
}


////////////////////////////////////////////////////////////////////
// Allocate memory and load targa bits. Returns pointer to new buffer,
// height, and width of texture, and the OpenGL format of data.
// Call free() on buffer when finished!
// This only works on pretty vanilla targas... 8, 24, or 32 bit color
// only, no palettes, no RLE encoding.
GLbyte* gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	//FILE *pFile;					// File pointer
	lge::FileHandle tgaFile;		// File pointer
	lge::FileError fileError;		// File operation error code
	TGAHEADER tgaHeader;			// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;					// Pixel depth;
	GLbyte	*pBits = nullptr;		// Pointer to bits

	// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_RGB;
	*iComponents = GL_RGB;

	// Attempt to open the file
	//*
	fileError = lge::File::open(tgaFile, szFileName, lge::FileMode::FILE_READ , true);
	if (fileError != lge::FileError::FILE_SUCCESS)
	{
		//assert(fileError != lge::FileError::FILE_OPEN_FAIL);
		return nullptr;
	}
	//*/
	/*
	fopen_s(&pFile, szFileName, "rb");
	if (pFile == NULL)
	{
		return nullptr;
	}
	//*/
	

	// Read in header (binary)
	//fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);
	//*
	fileError = lge::File::read(tgaFile, &tgaHeader, sizeof(TGAHEADER));
	DWORD windowsError = GetLastError();
	windowsError;
	if (fileError != lge::FileError::FILE_SUCCESS)
	{
		assert(fileError != lge::FileError::FILE_READ_FAIL);
		fileError = lge::File::close(tgaFile);
		assert(fileError != lge::FileError::FILE_CLOSE_FAIL);
		return nullptr;
	}
	//*/

	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
	{
		// Complain
		bool badTgaBits = true;
		badTgaBits;
		assert(!badTgaBits);

		// Leave
		fileError = lge::File::close(tgaFile);
		assert(fileError != lge::FileError::FILE_CLOSE_FAIL);
		//fclose(pFile);
		return nullptr;
	}

	// Calculate size of image buffer
	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == nullptr)
	{
		// Complain
		bool badTgaAlloc = true;
		badTgaAlloc;
		assert(!badTgaAlloc);

		// Leave
		fileError = lge::File::close(tgaFile);
		assert(fileError != lge::FileError::FILE_CLOSE_FAIL);
		//fclose(pFile);
		return nullptr;
	}


	// Read in the bits
	// Check for read error. This should catch RLE or other weird formats
	//*
	fileError = lge::File::read(tgaFile, pBits, lImageSize);
	if (fileError != lge::FileError::FILE_SUCCESS)
	{
		assert(fileError != lge::FileError::FILE_READ_FAIL);
		fileError = lge::File::close(tgaFile);
		assert(fileError != lge::FileError::FILE_CLOSE_FAIL);
		free(pBits);
		return nullptr;

	}
	//*/
	/*
	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		fclose(pFile);
		return nullptr;
	}
	//*/



	// Set OpenGL format expected
	switch (sDepth)
	{

		case 3:     // Most likely case
			*eFormat = GL_BGR;
			*iComponents = GL_RGB;
			break;

		case 4:
			*eFormat = GL_BGRA;
			*iComponents = GL_RGBA;
			break;
		case 1:
			//free(pBits);
			//fclose(pFile);

			fileError = lge::File::close(tgaFile);
			assert(fileError != lge::FileError::FILE_CLOSE_FAIL);
			free(pBits);
			
			return nullptr;

			// bad case - keenan
			// I commented out
			//  *eFormat = GL_LUMINANCE;
			//  *iComponents = GL_LUMINANCE;
			break;
		default:        // RGB
			// If on the iPhone, TGA's are BGR, and the iPhone does not 
			// support BGR without alpha, but it does support RGB,
			// so a simple swizzle of the red and blue bytes will suffice.
			// For faster iPhone loads however, save your TGA's with an Alpha!

			break;
	}


	// Done with File
	//fclose(pFile);
	//*
	fileError = lge::File::close(tgaFile);
	if (fileError != lge::FileError::FILE_SUCCESS)
	{
		assert(fileError != lge::FileError::FILE_CLOSE_FAIL);
		free(pBits);
		return nullptr;
	}
	//*/


	
	GLbyte isOriginUpperLeft = tgaHeader.descriptor & 0x20;	// 0x20 is the 5th bit (from right 0-7 bits) that describes the image's origins


	// If the origin is not upper
	if (!isOriginUpperLeft)
	{
		// Flip the bits!
		pBits = jisFlipTarga(*iWidth, *iHeight, sDepth, sizeof(GLbyte), pBits);
	}

	// Return pointer to image data
	return pBits;
}