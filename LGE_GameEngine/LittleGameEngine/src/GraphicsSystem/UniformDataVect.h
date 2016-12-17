#ifndef LGE_UNIFORM_DATA_VECT_H
#define LGE_UNIFORM_DATA_VECT_H

#include "UniformData.h"

namespace lge
{
	// A Uniform property that holds a Vect
	class UniformDataVect : public UniformData
	{
	public:

		//
		// Ctor / Dtor
		//

		// Ctor
		UniformDataVect(ShaderUniformHandle* const newHandle);

		// Dtor
		virtual ~UniformDataVect();



		//
		// Contracts
		//

		// Retrieve the data type for this Uniform (should be Vector4)
		virtual UniformType GetDataType() const override;

		// Update the uniform data by passing it into the shader
		virtual void UpdateUniform() override;


		// Set the Vect value of this Uniform
		virtual void SetUniform(const Vect& newValue) override;
		

		// Will assert! Do not call
		virtual void SetUniform(const Matrix& newValue) override;
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

		Vect* data;
	};
}
#endif