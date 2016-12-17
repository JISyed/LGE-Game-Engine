#ifndef LGE_MATERIAL_UNIFORM_H
#define LGE_MATERIAL_UNIFORM_H

#include "enumTextureUnit.h"
#include "UniformNameHelper.h"

namespace lge
{
	// Forward declares
	class UniformData;
	class ShaderUniformHandle;
	class Matrix;
	class Vect;


	// Represents a uniform property of a Material that is user-settable
	class MaterialUniform
	{
	public:

		//
		// Ctor / Dtor
		//

		MaterialUniform(ShaderUniformHandle* const shaderUniform);
		~MaterialUniform();



		//
		// Getters
		//

		// Needed for GenericListNode
		const unsigned int GetId() const;

		// Get the name of this Uniform
		const UniformName GetName() const;

		// Get the data type of this Uniform
		const UniformType GetDataType() const;



		//
		// Setters
		//

		// Set a Matrix value to this Uniform. Make sure the data type is correct first
		void SetUniformValue(const Matrix& newValue);
		// Set a Vect value to this Uniform. Make sure the data type is correct first
		void SetUniformValue(const Vect& newValue);
		// Set a float value to this Uniform. Make sure the data type is correct first
		void SetUniformValue(const float newValue);
		// Set an int value to this Uniform. Make sure the data type is correct first
		void SetUniformValue(const int newValue);
		// Set a texture unit value to this Uniform. Make sure the data type is correct first
		void SetUniformValue(const TextureUnit newValue);
		// Set a matrix array value to this Uniform. Make sure the data type is correct first
		void SetUniformValue(const Matrix* const newValue);


		//
		// Methods
		//

		// Send the currently set uniform value into the Material's shader (in the GPU)
		void SendUniformIntoGpu();




	private:

		//
		// Data 
		//

		const UniformName name;
		const UniformType type;
		UniformData* data;





		//
		// Deleted Methods
		//

		// No copy ctor
		MaterialUniform(const MaterialUniform& other) = delete;

		// No copy assignment
		MaterialUniform& operator=(const MaterialUniform& other) = delete;

		// No move ctor
		MaterialUniform(MaterialUniform&& other) = delete;

		// No move assignment
		MaterialUniform& operator=(MaterialUniform&& other) = delete;
	};

	
}
#endif