#ifndef LGE_UNIFORM_DATA_H
#define LGE_UNIFORM_DATA_H

#include "UniformNameHelper.h"
#include "enumTextureUnit.h"

namespace lge
{
	// Forward declare
	class ShaderUniformHandle;
	class Matrix;
	class Vect;


	// Represents a single settable uniform property in the material.
	// Must inherit to get different uniform data types.
	class UniformData
	{
	public:

		//
		// Ctor / Dtor
		//

		// Ctor
		UniformData(ShaderUniformHandle* const newHandle);
		
		// Dtor
		virtual ~UniformData();



		//
		// Contracts
		//

		// Retrieve the data type for this Uniform
		virtual UniformType GetDataType() const = 0;

		// Update the uniform data by passing it into the shader
		virtual void UpdateUniform() = 0;

		// Setup the local copy of the uniform data, if its valid
		virtual void SetUniform(const Matrix& newValue) = 0;
		// Setup the local copy of the uniform data, if its valid
		virtual void SetUniform(const Vect& newValue) = 0;
		// Setup the local copy of the uniform data, if its valid
		virtual void SetUniform(const float newValue) = 0;
		// Setup the local copy of the uniform data, if its valid
		virtual void SetUniform(const int newValue) = 0;
		// Setup the local copy of the uniform data, if its valid
		virtual void SetUniform(const TextureUnit newValue) = 0;
		// Setup the local copy of the uniform data, if its valid
		virtual void SetUniform(const Matrix* const newValueArray) = 0;




	protected:

		//
		// Data
		//

		// The uniform handle from the shader
		ShaderUniformHandle* const handle;



		//
		// Deleted Methods
		//

		// No Copy Assignment overload
		UniformData& operator=(const UniformData& other) = delete;

		// No copy ctor
		UniformData(const UniformData& other) = delete;

		// No move ctor
		UniformData(UniformData&& other) = delete;

		// No move assignment
		UniformData& operator=(UniformData&& other) = delete;
	};
}

#endif