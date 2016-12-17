#include "UniformDataInt.h"
#include "MathEngine.h"
#include "ShaderUniformHandle.h"
#include <cassert>

namespace lge
{
	// Ctor
	UniformDataInt::UniformDataInt(ShaderUniformHandle* const newHandle) :
		UniformData(newHandle),
		data(0)
	{
	}

	// VIRTUAL
	// Dtor
	UniformDataInt::~UniformDataInt()
	{
	}





	// VIRTUAL
	// Retrieve the data type for this Uniform (should be Int)
	UniformType UniformDataInt::GetDataType() const
	{
		return UniformType::SignedInt;
	}

	// VIRTUAL
	// Update the uniform data by passing it into the shader
	void UniformDataInt::UpdateUniform()
	{
		this->handle->SetUniformValue(this->data);
	}




	// VIRTUAL
	// Set the int value of this Uniform
	void UniformDataInt::SetUniform(const int newValue)
	{
		this->data = newValue;
	}




	// VIRTUAL
	// Will assert! Do not call
	void UniformDataInt::SetUniform(const Matrix& newValue)
	{
		// UniformDataInt cannot set a Matrix!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataInt::SetUniform(const Vect& newValue)
	{
		// UniformDataInt cannot set a Vect!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataInt::SetUniform(const float newValue)
	{
		// UniformDataInt cannot set a float!
		newValue;
		assert(false);
	}
	
	// VIRTUAL
	// Will assert! Do not call
	void UniformDataInt::SetUniform(const TextureUnit newValue)
	{
		// UniformDataInt cannot set a TextureUnit!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataInt::SetUniform(const Matrix* const newValueArray)
	{
		// UniformDataInt cannot set a TextureUnit!
		newValueArray;
		assert(false);
	}

}