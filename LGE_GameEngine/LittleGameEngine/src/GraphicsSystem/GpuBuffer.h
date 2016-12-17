#ifndef H_LGE_GPU_BUFFER
#define H_LGE_GPU_BUFFER

#include "GL\gl3w.h"


namespace lge
{
	// The access level of a GPU data buffer
	enum class GpuBufferAccess : unsigned int
	{
		StaticDraw = GL_STATIC_DRAW,
		StaticRead = GL_STATIC_READ,
		StaticCopy = GL_STATIC_COPY,
		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY,
	};

	// The type of GPU buffer
	enum class GpuBufferType : unsigned int
	{
		TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
		ArrayBuffer = GL_ARRAY_BUFFER,
		UniformBuffer = GL_UNIFORM_BUFFER,
	};


	// Represents a data buffer in the GPU
	class GpuBuffer
	{
	public:

		//
		// Ctor / Dtor
		//

		GpuBuffer(const GpuBufferType type, const GpuBufferAccess access, const size_t numberOfElements, const size_t elementSize, const void* const data);
		~GpuBuffer();


		//
		// Methods
		//


		// Write to a certain subregion of the GpuBuffer (should probably not be called often)
		void SetSubRegion(const GLintptr startingOffset, const size_t numOfElementsToWrite, const void* const subRegionData);

		// Activate the buffer as a specified type (for GPU Program)
		void ActivateAs(const GpuBufferType type);

		// Prepare this buffer for GpuProgram output
		void PrepareAsOutput();

		// Prepare this buffer for GpuProgram input (uniform buffer)
		void PrepareAsUniformInput();

		// Prepare a range in this buffer for GpuProgram output (returns the element range)
		const size_t PrepareRangeAsOutput(const size_t startingElement, const size_t endingElement);

		// Get data out of the buffer
		void GetBufferData(void* const cpuBuffer, const size_t cpuBufferSize);


		//
		// Accessors
		//

		const size_t GetNumberOfElements() const;
		const size_t GetElementSize() const;



	private:

		//
		// Data
		//

		GLuint vbo;						// OpenGL handle
		size_t numOfElements;			// Number of elements in this buffer
		size_t sizeOfElements;			// The size of each element in this buffer
		GpuBufferType bufferType;		// Type of OpenGL buffer
		GpuBufferAccess bufferAccess;	// The access level of buffer



		//
		// Private Routines
		//

		// Activate this buffer
		void Activate();


		//
		// Deleted Methods
		//


		// No default ctor
		GpuBuffer() = delete;

		// No copy assignment
		GpuBuffer& operator=(const GpuBuffer& other) = delete;

		// No copy ctor
		GpuBuffer(const GpuBuffer& other) = delete;

		// No move ctor
		GpuBuffer(GpuBuffer&& other) = delete;

		// No move assignment
		GpuBuffer& operator=(GpuBuffer&& other) = delete;

	};
}
#endif