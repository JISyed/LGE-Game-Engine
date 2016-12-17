#include "UniformDataVect.h"
#include "ShaderUniformHandle.h"
#include "MathEngine.h"
#include <cassert>

namespace lge
{
	// Ctor
	UniformDataVect::UniformDataVect(ShaderUniformHandle* const newHandle) :
		UniformData(newHandle),
		data(new Vect())
	{
	}

	// VIRTUAL
	// Dtor
	UniformDataVect::~UniformDataVect()
	{
		delete this->data;
	}




	// VIRTUAL
	// Retrieve the data type for this Uniform (should be Vector4)
	UniformType UniformDataVect::GetDataType() const
	{
		return UniformType::Vector4;
	}

	// VIRTUAL
	// Update the uniform data by passing it into the shader
	void UniformDataVect::UpdateUniform()
	{
		this->handle->SetUniformValue(*(this->data));
	}



	// VIRTUAL
	// Set the Vect value of this Uniform
	void UniformDataVect::SetUniform(const Vect& newValue)
	{
		*(this->data) = newValue;
	}



	// VIRTUAL
	// Will assert! Do not call
	void UniformDataVect::SetUniform(const Matrix& newValue)
	{
		// UniformDataVect cannot set a Matrix!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataVect::SetUniform(const float newValue)
	{
		// UniformDataVect cannot set a float!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataVect::SetUniform(const int newValue)
	{
		// UniformDataVect cannot set an int!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataVect::SetUniform(const TextureUnit newValue)
	{
		// UniformDataVect cannot set a TextureUnit!
		newValue;
		assert(false);
	}

	// VIRTUAL
	// Will assert! Do not call
	void UniformDataVect::SetUniform(const Matrix* const newValueArray)
	{
		// UniformDataVect cannot set a TextureUnit!
		newValueArray;
		assert(false);
	}


}