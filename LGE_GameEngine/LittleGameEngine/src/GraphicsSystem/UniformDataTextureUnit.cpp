#include "UniformDataTextureUnit.h"
#include "MathEngine.h"
#include "ShaderUniformHandle.h"
#include <cassert>

namespace lge
{
	// Ctor
	UniformDataTextureUnit::UniformDataTextureUnit(ShaderUniformHandle* const newHandle) :
		UniformData(newHandle),
		data(TextureUnit::u0)
	{
	}

	// VIRTUAL
	// Dtor
	UniformDataTextureUnit::~UniformDataTextureUnit()
	{
	}






	// VIRTUAL
	// Retrieve the data type for this Uniform (should be TextureUnit)
	UniformType UniformDataTextureUnit::GetDataType() const
	{
		return UniformType::TextureUnit;
	}

	// VIRTUAL
	// Update the uniform data by passing it into the shader
	void UniformDataTextureUnit::UpdateUniform()
	{
		this->handle->SetUniformValue(this->data);
	}






	// VIRTUAL
	// Set the TextureUnit value of this Uniform
	void UniformDataTextureUnit::SetUniform(const TextureUnit newValue)
	{
		this->data = newValue;
	}




	// VIRTUAL
	// Will assert! Do not call
	void UniformDataTextureUnit::SetUniform(const Matrix& newValue)
	{
		// UniformDataTextureUnit cannot set a Matrix!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataTextureUnit::SetUniform(const Vect& newValue)
	{
		// UniformDataTextureUnit cannot set a Vect!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataTextureUnit::SetUniform(const float newValue)
	{
		// UniformDataTextureUnit cannot set a float!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataTextureUnit::SetUniform(const int newValue)
	{
		// UniformDataTextureUnit cannot set an int!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataTextureUnit::SetUniform(const Matrix* const newValueArray)
	{
		// UniformDataTextureUnit cannot set an int!
		newValueArray;
		assert(false);
	}


}