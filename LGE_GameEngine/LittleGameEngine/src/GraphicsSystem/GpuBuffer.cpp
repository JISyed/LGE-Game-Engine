#include "GpuBuffer.h"
#include <cassert>
#include "GpuBufferVao.h"

namespace lge
{
	GpuBuffer::GpuBuffer(const GpuBufferType type, const GpuBufferAccess access, const size_t numberOfElements, const size_t elementSize, const void* const data):
		vbo(0u),
		numOfElements(numberOfElements),
		sizeOfElements(elementSize),
		bufferType(type),
		bufferAccess(access)
	{
		GpuBufferVao::Activate();

		glGenBuffers(1, &this->vbo);
		this->Activate();
		glBufferData((GLenum)this->bufferType, this->numOfElements * this->sizeOfElements, data, (GLenum)this->bufferAccess);

		GpuBufferVao::Unactivate();
	}

	GpuBuffer::~GpuBuffer()
	{
		GpuBufferVao::Activate();

		glDeleteBuffers(1, &this->vbo);

		GpuBufferVao::Unactivate();
	}


	void GpuBuffer::SetSubRegion(const GLintptr startingOffset, const size_t numOfElementsToWrite, const void* const subRegionData)
	{
		GpuBufferVao::Activate();

		// Writing too many elements
		assert(numOfElementsToWrite <= this->numOfElements);

		// Don't write out of bounds
		assert(startingOffset + numOfElementsToWrite <= this->numOfElements);

		this->Activate();
		glBufferSubData((GLenum)this->bufferType, (GLintptr)(startingOffset * this->sizeOfElements), (GLsizeiptr)(numOfElementsToWrite * this->sizeOfElements), subRegionData);

		GpuBufferVao::Unactivate();
	}


	void GpuBuffer::Activate()
	{
		glBindBuffer((GLenum)this->bufferType, this->vbo);
	}

	// Activate the buffer as a specified type
	void GpuBuffer::ActivateAs(const GpuBufferType type)
	{
		glBindBuffer((GLenum)type, this->vbo);
	}


	// Prepare this buffer for GpuProgram output
	void GpuBuffer::PrepareAsOutput()
	{
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, this->vbo);
	}

	// Prepare this buffer for GpuProgram input (uniform buffer)
	void GpuBuffer::PrepareAsUniformInput()
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, this->vbo);
	}

	// Prepare a range in this buffer for GpuProgram output (returns the element range)
	const size_t GpuBuffer::PrepareRangeAsOutput(const size_t startingElement, const size_t endingElement)
	{
		const size_t elementRange = endingElement - startingElement;
		assert(elementRange <= this->numOfElements);

		glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, 0, this->vbo, (GLintptr)(startingElement * this->sizeOfElements), (GLsizeiptr)(endingElement * this->sizeOfElements));

		return elementRange;
	}


	// Get data out of the buffer
	void GpuBuffer::GetBufferData(void* const cpuBuffer, const size_t cpuBufferSize)
	{
		size_t bytesWritten = this->numOfElements * this->sizeOfElements;
		if (cpuBufferSize < bytesWritten)
		{
			bytesWritten = cpuBufferSize;
		}

		this->ActivateAs(GpuBufferType::TransformFeedbackBuffer);

		glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, bytesWritten, cpuBuffer);
	}


	const size_t GpuBuffer::GetNumberOfElements() const
	{
		return this->numOfElements;
	}

	const size_t GpuBuffer::GetElementSize() const
	{
		return this->sizeOfElements;
	}

}