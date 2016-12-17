#ifndef LGE_UNIFORM_DATA_MATRIX_H
#define LGE_UNIFORM_DATA_MATRIX_H

#include "UniformData.h"

namespace lge
{
	// A Uniform property that holds a Matrix
	class UniformDataMatrix : public UniformData
	{
	public:

		//
		// Ctor / Dtor
		//

		// Ctor
		UniformDataMatrix(ShaderUniformHandle* const newHandle);

		// Dtor
		virtual ~UniformDataMatrix();



		//
		// Contracts
		//

		// Retrieve the data type for this Uniform (should be Matrix4x4)
		virtual UniformType GetDataType() const override;

		// Update the uniform data by passing it into the shader
		virtual void SetUniform(const Matrix& newValue) override;



		// Set the Matrix value of this Uniform
		virtual void UpdateUniform() override;



		// Will assert! Do not call
		virtual void SetUniform(const Vect& newValue) override;
		// Will assert! Do not call
		virtual void SetUniform(const float newValue) override;
		// Will assert! Do not call
		virtual void SetUniform(const int newValue) override;
		// Will assert! Do not call
		virtual void SetUniform(const TextureUnit newValue) override;
		// Will assert! Do not call
		virtual void SetUniform(const Matrix* const newValueArray) override;




	private:

		//
		// Data
		//

		Matrix* data;
	};
}
#endif