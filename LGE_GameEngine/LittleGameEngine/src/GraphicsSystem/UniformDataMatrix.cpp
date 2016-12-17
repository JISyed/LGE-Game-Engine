#include "UniformDataMatrix.h"
#include "ShaderUniformHandle.h"
#include "MathEngine.h"
#include <cassert>

namespace lge
{
	// Ctor
	UniformDataMatrix::UniformDataMatrix(ShaderUniformHandle* const newHandle) :
		UniformData(newHandle),
		data(new Matrix())
	{
	}

	// VIRTUAL
	// Dtor
	UniformDataMatrix::~UniformDataMatrix()
	{
		delete this->data;
	}




	// VIRTUAL
	// Retrieve the data type for this Uniform (should be Matrix4x4)
	UniformType UniformDataMatrix::GetDataType() const
	{
		return UniformType::Matrix4x4;
	}

	// VIRTUAL
	// Update the uniform data by passing it into the shader
	void UniformDataMatrix::UpdateUniform()
	{
		this->handle->SetUniformValue(*(this->data));
	}




	// VIRTUAL
	// Set the Matrix value of this Uniform
	void UniformDataMatrix::SetUniform(const Matrix& newValue)
	{
		*(this->data) = newValue;
	}





	// VIRTUAL
	// Will assert! Do not call
	void UniformDataMatrix::SetUniform(const Vect& newValue)
	{
		// UniformDataMatrix cannot set a Vect!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataMatrix::SetUniform(const float newValue)
	{
		// UniformDataMatrix cannot set a float!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataMatrix::SetUniform(const int newValue)
	{
		// UniformDataMatrix cannot set an int!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataMatrix::SetUniform(const TextureUnit newValue)
	{
		// UniformDataMatrix cannot set a TextureUnit!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataMatrix::SetUniform(const Matrix* const newValueArray)
	{
		// UniformDataMatrix cannot set a TextureUnit!
		newValueArray;
		assert(false);
	}


}