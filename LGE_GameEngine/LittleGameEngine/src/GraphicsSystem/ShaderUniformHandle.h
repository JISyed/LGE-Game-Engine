#ifndef LGE_SHADER_UNIFORM_HANDLE_H
#define LGE_SHADER_UNIFORM_HANDLE_H

#include "UniformNameHelper.h"
#include "GL\gl3w.h"
#include "enumTextureUnit.h"

namespace lge
{
	// Forward declares
	class Matrix;
	class Vect;


	// Is responsible for being a fast link between OpenGL Uniforms and our engine.
	// Different uniform names are defined in "UniformNameHelper.h".
	class ShaderUniformHandle
	{
	public:
		
		//
		// Big Four + Special Ctor
		//

		ShaderUniformHandle();
		ShaderUniformHandle(const UniformName newName, const UniformType newDataType, const GLint openglHandle);
		ShaderUniformHandle(const ShaderUniformHandle& other);
		// Copy
		ShaderUniformHandle& operator=(const ShaderUniformHandle& other);
		// Move
		ShaderUniformHandle& operator=(ShaderUniformHandle&& other);
		~ShaderUniformHandle();



		//
		// Setters
		//

		// This set method should only be called by the UniformData instances.
		// No data type checks are done here!!!
		void SetUniformValue(const Matrix& newValue);
		// This set method should only be called by the UniformData instances.
		// No data type checks are done here!!!
		void SetUniformValue(const Vect& newValue);
		// This set method should only be called by the UniformData instances.
		// No data type checks are done here!!!
		void SetUniformValue(const float newValue);
		// This set method should only be called by the UniformData instances.
		// No data type checks are done here!!!
		void SetUniformValue(const int newValue);
		// This set method should only be called by the UniformData instances.
		// No data type checks are done here!!!
		void SetUniformValue(const TextureUnit newValue);
		// This set method should only be called by the UniformData instances.
		// No data type checks are done here!!!
		void SetUniformValue(const Matrix* const newValueArray, const int arraySize);



		//
		// Getters
		//

		// Get this uniform's name in the shader
		const UniformName GetName() const;

		// Get the data type of this uniform
		const UniformType GetDataType() const;




	private:

		//
		// Data
		//

		UniformName name;
		UniformType dataType;
		GLint openglLocation;



		//
		// Deleted Methods
		//

		// No move ctor
		ShaderUniformHandle(ShaderUniformHandle&& other) = delete;
	};
}
#endif