#include "UniformDataFloat.h"
#include "MathEngine.h"
#include "ShaderUniformHandle.h"
#include <cassert>

namespace lge
{
	// Ctor
	UniformDataFloat::UniformDataFloat(ShaderUniformHandle* const newHandle) :
		UniformData(newHandle),
		data(0.0f)
	{
	}

	// VIRTUAL
	// Dtor
	UniformDataFloat::~UniformDataFloat()
	{
	}




	// VIRTUAL
	// Retrieve the data type for this Uniform (should be Float)
	UniformType UniformDataFloat::GetDataType() const
	{
		return UniformType::Float;
	}

	// VIRTUAL
	// Update the uniform data by passing it into the shader
	void UniformDataFloat::UpdateUniform()
	{
		this->handle->SetUniformValue(this->data);
	}






	// VIRTUAL
	// Set the float value of this Uniform
	void UniformDataFloat::SetUniform(const float newValue)
	{
		this->data = newValue;
	}




	// VIRTUAL
	// Will assert! Do not call
	void UniformDataFloat::SetUniform(const Matrix& newValue)
	{
		// UniformDataFloat cannot set a Matrix!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataFloat::SetUniform(const Vect& newValue)
	{
		// UniformDataFloat cannot set a Vect!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataFloat::SetUniform(const int newValue)
	{
		// UniformDataFloat cannot set an int!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataFloat::SetUniform(const TextureUnit newValue)
	{
		// UniformDataFloat cannot set a TextureUnit!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataFloat::SetUniform(const Matrix* const newValueArray)
	{
		// UniformDataFloat cannot set a TextureUnit!
		newValueArray;
		assert(false);
	}
}