#ifndef LGE_IMAGE_BUFFER_H
#define LGE_IMAGE_BUFFER_H

namespace lge
{
	// Used by ImageBuffer to define sizes for renderable images using powers-of-two (in pixels)
	enum class ImageSizes : unsigned int
	{
		aPx1 = 1u,
		bPx2 = 2u,
		cPx4 = 4u,
		dPx8 = 8u,
		ePx16 = 16u,
		fPx32 = 32u,
		gPx64 = 64u,
		hPx128 = 128u,
		iPx256 = 256u,
		jPx512 = 512u,
		kPx1024 = 1024u,
		lPx2048 = 2048u
	};


	// Acts as CPU accessable storage for image data before being sent into the GPU via Textures. Only RGB format supported!
	class ImageBuffer
	{
	public:

		//
		// Big Four
		//

		// Ctor
		ImageBuffer(const ImageSizes newWidth, const ImageSizes newHeight);
		// Dtor
		~ImageBuffer();
		// Move ctor
		ImageBuffer(ImageBuffer&& other);
		// Move assignment
		ImageBuffer& operator=(ImageBuffer&& other);



		//
		// Getters
		//

		// Get width of image in pixels
		const size_t GetWidth() const;

		// Get height of image in pixels
		const size_t GetHeight() const;

		// Get read-only pointer to the raw image buffer (ImageBuffer must still exist!)
		const unsigned char* const GetReadOnlyRawData() const;



		//
		// Setters
		//

		// Set the grayscale value of the specified pixel (x right-to-left, y top-to-bottom)
		void SetPixelGrayscale(const float grayValue, const unsigned int x, const unsigned int y);
		
		// Set the grayscale value of the specified pixel (x right-to-left, y top-to-bottom)
		void SetPixelGrayscale(const unsigned char grayValue, const unsigned int x, const unsigned int y);


		// Set the color value of the specified pixel (x right-to-left, y top-to-bottom)
		void SetPixelColor(const float r, const float g, const float b, const unsigned int x, const unsigned int y);

		// Set the color value of the specified pixel (x right-to-left, y top-to-bottom)
		void SetPixelColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned int x, const unsigned int y);



		//
		// Helpers
		// 

		// Clear the entire image to a given color. NOTICE: Potentially slow for large images
		void ClearToColor(const float r, const float g, const float b);

		// Clear the entire image to a given color. NOTICE: Potentially slow for large images
		void ClearToColor(const unsigned char r, const unsigned char g, const unsigned char b);

		// Force the float to be between values of 0f and 1f
		static const float ClampFloat(const float f);


	private:

		//
		// Data
		//

		unsigned char* rawData;
		size_t width;
		size_t height;




		//
		// Helper Methods
		//

		

		// Take a float from 0f to 1f, and make it a byte between 0x00 and 0xFF
		const unsigned char FloatToByte(const float f);




		//
		// Deleted Methods
		//

		// No copy assignment
		ImageBuffer& operator=(const ImageBuffer& other) = delete;

		// No copy ctor
		ImageBuffer(const ImageBuffer& other) = delete;

		// Default
		ImageBuffer() = delete;
		

	};

	
}

#endif