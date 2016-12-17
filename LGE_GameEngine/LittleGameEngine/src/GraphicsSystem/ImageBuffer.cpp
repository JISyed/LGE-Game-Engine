#include "ImageBuffer.h"
#include <cassert>

#define IMAGE_BUFFER_COLOR_DEPTH 3u
#define RED_OFFSET 0u
#define GREEN_OFFSET 1u
#define BLUE_OFFSET 2u

namespace lge
{
	// Ctor
	ImageBuffer::ImageBuffer(const ImageSizes newWidth, const ImageSizes newHeight) :
		width((size_t) newWidth),
		height((size_t) newHeight)
	{
		this->rawData = new unsigned char[this->width * this->height * IMAGE_BUFFER_COLOR_DEPTH];
	}

	// Dtor
	ImageBuffer::~ImageBuffer()
	{
		if (this->rawData != nullptr)
		{
			delete[] this->rawData;
		}
	}

	// Move ctor
	ImageBuffer::ImageBuffer(ImageBuffer&& other) :
		width(other.width),
		height(other.height),
		rawData(other.rawData)
	{
		// Image data is moved, so clear values of old ImageBuffer
		other.width = 0u;
		other.height = 0u;
		other.rawData = nullptr;
	}

	// Move assignment
	ImageBuffer& ImageBuffer::operator=(ImageBuffer&& other)
	{
		// Moving to yourself doesn't make sense
		if (this == &other)
		{
			return *this;
		}

		// Move old data into new data
		this->width = other.width;
		this->height = other.height;
		this->rawData = other.rawData;

		// Image data is moved, so clear values of old ImageBuffer
		other.width = 0u;
		other.height = 0u;
		other.rawData = nullptr;

		return *this;
	}



	// Get width of image in pixels
	const size_t ImageBuffer::GetWidth() const
	{
		return this->width;
	}

	// Get height of image in pixels
	const size_t ImageBuffer::GetHeight() const
	{
		return this->height;
	}

	// Get read-only pointer to the raw image buffer
	const unsigned char* const ImageBuffer::GetReadOnlyRawData() const
	{
		return this->rawData;
	}




	// Set the grayscale value of the specified pixel (x right-to-left, y top-to-bottom)
	void ImageBuffer::SetPixelGrayscale(const float grayValue, const unsigned int x, const unsigned int y)
	{
		assert(x < this->width);
		assert(y < this->height);

		this->SetPixelGrayscale(FloatToByte(grayValue), x, y);
	}

	// Set the grayscale value of the specified pixel (x left-to-right, y top-to-bottom) (both starting at 0)
	void ImageBuffer::SetPixelGrayscale(const unsigned char grayValue, const unsigned int x, const unsigned int y)
	{
		assert(x < this->width);
		assert(y < this->height);

		const size_t rawWidth = this->width * IMAGE_BUFFER_COLOR_DEPTH;
		const size_t xIncrement = x * IMAGE_BUFFER_COLOR_DEPTH;
		const size_t yIncrement = y * rawWidth;

		this->rawData[xIncrement + yIncrement + RED_OFFSET] = grayValue;
		this->rawData[xIncrement + yIncrement + GREEN_OFFSET] = grayValue;
		this->rawData[xIncrement + yIncrement + BLUE_OFFSET] = grayValue;
	}


	// Set the color value of the specified pixel (x right-to-left, y top-to-bottom)
	void ImageBuffer::SetPixelColor(const float r, const float g, const float b, const unsigned int x, const unsigned int y)
	{
		assert(x < this->width);
		assert(y < this->height);

		this->SetPixelColor(FloatToByte(r), FloatToByte(g), FloatToByte(b), x, y);
	}

	// Set the color value of the specified pixel (x right-to-left, y top-to-bottom)
	void ImageBuffer::SetPixelColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned int x, const unsigned int y)
	{
		assert(x < this->width);
		assert(y < this->height);

		const size_t rawWidth = this->width * IMAGE_BUFFER_COLOR_DEPTH;
		const size_t xIncrement = x * IMAGE_BUFFER_COLOR_DEPTH;
		const size_t yIncrement = y * rawWidth;

		this->rawData[xIncrement + yIncrement + RED_OFFSET] = r;
		this->rawData[xIncrement + yIncrement + GREEN_OFFSET] = g;
		this->rawData[xIncrement + yIncrement + BLUE_OFFSET] = b;
	}




	// Clear the entire image to a given color. NOTICE: Potentially slow for large images
	void ImageBuffer::ClearToColor(const float r, const float g, const float b)
	{
		this->ClearToColor(FloatToByte(r), FloatToByte(g), FloatToByte(b));
	}

	// Clear the entire image to a given color. NOTICE: Potentially slow for large images
	void ImageBuffer::ClearToColor(const unsigned char r, const unsigned char g, const unsigned char b)
	{
		const size_t bufferSize = this->width * this->height * IMAGE_BUFFER_COLOR_DEPTH;

		for (size_t i = 0u; i < bufferSize; i += IMAGE_BUFFER_COLOR_DEPTH)
		{
			this->rawData[i + RED_OFFSET] = r;
			this->rawData[i + GREEN_OFFSET] = g;
			this->rawData[i + BLUE_OFFSET] = b;
		}
	}



	// STATIC
	// Force the float to be between values of 0f and 1f
	const float ImageBuffer::ClampFloat(const float f)
	{
		float newValue = f;

		if (f < 0.0f)
		{
			newValue = 0.0f;
		}
		else if (f > 1.0f)
		{
			newValue = 1.0f;
		}

		return newValue;
	}

	// Take a float from 0f to 1f, and make it a byte between 0x00 and 0xFF
	const unsigned char ImageBuffer::FloatToByte(const float f)
	{
		return (unsigned char) (f * (float)0xFF);
	}

}