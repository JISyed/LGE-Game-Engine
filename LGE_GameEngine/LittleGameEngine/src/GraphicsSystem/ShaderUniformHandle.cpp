#include "ShaderUniformHandle.h"

#include "MathEngine.h"

namespace lge
{
	ShaderUniformHandle::ShaderUniformHandle()
	{
	}

	ShaderUniformHandle::ShaderUniformHandle(UniformName newName, UniformType newDataType, GLint openglHandle) :
		name(newName),
		dataType(newDataType),
		openglLocation(openglHandle)
	{
	}

	ShaderUniformHandle::ShaderUniformHandle(const ShaderUniformHandle& other) :
		name(other.name),
		dataType(other.dataType),
		openglLocation(other.openglLocation)
	{
	}

	ShaderUniformHandle::~ShaderUniformHandle()
	{
	}

	ShaderUniformHandle& ShaderUniformHandle::operator=(const ShaderUniformHandle& other)
	{
		if (this == &other)
		{
			return *this;
		}

		this->name = other.name;
		this->dataType = other.dataType;
		this->openglLocation = other.openglLocation;

		return *this;
	}

	ShaderUniformHandle& ShaderUniformHandle::operator=(ShaderUniformHandle&& other)
	{
		if (this == &other)
		{
			return *this;
		}

		this->name = other.name;
		this->dataType = other.dataType;
		this->openglLocation = other.openglLocation;

		return *this;
	}





	void ShaderUniformHandle::SetUniformValue(const Matrix& newValue)
	{
		glUniformMatrix4fv(this->openglLocation, 1, GL_FALSE, (const float *)&newValue);
	}

	void ShaderUniformHandle::SetUniformValue(const Vect& newValue)
	{
		glUniform4fv(this->openglLocation, 1, (const float*)&newValue);
	}

	void ShaderUniformHandle::SetUniformValue(const float newValue)
	{
		glUniform1f(this->openglLocation, (const GLfloat) newValue);
	}

	void ShaderUniformHandle::SetUniformValue(const int newValue)
	{
		glUniform1i(this->openglLocation, (const GLint)newValue);
	}

	void ShaderUniformHandle::SetUniformValue(const TextureUnit newValue)
	{
		// Explicitly cast TextureUnit enum into int
		glUniform1i(this->openglLocation, static_cast<int>(newValue));
	}

	void ShaderUniformHandle::SetUniformValue(const Matrix* const newValueArray, const int arraySize)
	{
		assert(newValueArray != nullptr);
		assert(arraySize > 0);

		glUniformMatrix4fv(this->openglLocation, arraySize, GL_FALSE, (const float *)newValueArray);
	}




	const UniformName ShaderUniformHandle::GetName() const
	{
		return this->name;
	}

	const UniformType ShaderUniformHandle::GetDataType() const
	{
		return this->dataType;
	}




}