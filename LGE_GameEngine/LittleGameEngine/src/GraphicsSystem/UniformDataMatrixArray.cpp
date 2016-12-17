#include "UniformDataMatrixArray.h"
#include "ShaderUniformHandle.h"
#include "MathEngine.h"
#include <cassert>

// Number of elements in a uniform matrix array
#define LGE_UNIFORM_MATRIX_ARRAY_SIZE 100

namespace lge
{
	// Ctor
	UniformDataMatrixArray::UniformDataMatrixArray(ShaderUniformHandle* const newHandle) :
		UniformData(newHandle),
		data(new Matrix[LGE_UNIFORM_MATRIX_ARRAY_SIZE])
	{
	}

	// VIRTUAL
	// Dtor
	UniformDataMatrixArray::~UniformDataMatrixArray()
	{
		delete[] this->data;
	}




	// VIRTUAL
	// Retrieve the data type for this Uniform (should be Matrix4x4)
	UniformType UniformDataMatrixArray::GetDataType() const
	{
		return UniformType::Matrix4x4Array;
	}

	// VIRTUAL
	// Update the uniform data by passing it into the shader
	void UniformDataMatrixArray::UpdateUniform()
	{
		this->handle->SetUniformValue(this->data, LGE_UNIFORM_MATRIX_ARRAY_SIZE);
	}




	// VIRTUAL
	// Set the Matrix value of this Uniform
	void UniformDataMatrixArray::SetUniform(const Matrix* const newValueArray)
	{
		memcpy(this->data, newValueArray, sizeof(Matrix) * LGE_UNIFORM_MATRIX_ARRAY_SIZE);
	}





	// VIRTUAL
	// Will assert! Do not call
	void UniformDataMatrixArray::SetUniform(const Vect& newValue)
	{
		// UniformDataMatrix cannot set a Vect!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataMatrixArray::SetUniform(const float newValue)
	{
		// UniformDataMatrix cannot set a float!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataMatrixArray::SetUniform(const int newValue)
	{
		// UniformDataMatrix cannot set an int!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataMatrixArray::SetUniform(const TextureUnit newValue)
	{
		// UniformDataMatrix cannot set a TextureUnit!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataMatrixArray::SetUniform(const Matrix& newValue)
	{
		// UniformDataMatrix cannot set a TextureUnit!
		newValue;
		assert(false);
	}


}