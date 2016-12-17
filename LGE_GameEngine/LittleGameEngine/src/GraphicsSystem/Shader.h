#ifndef LGE_SHADER_H
#define LGE_SHADER_H

#include "GL/gl3w.h"
#include "..\EngineUtilities\IdGenerator.h"

namespace lge
{
	// Forward declares
	class ShaderUniformHandle;
	class GpuBuffer;

	// TEMP: Find a better way to dynamically name shaders
	enum class ShaderName : unsigned int
	{
		BlinnPhong,
		ConstantColor,
		ConstantTexture,
		DiffuseTexture,
		VertexRainbow,
		NormalDiffuseTexture,
		NormalSpecularTexture,
		SkinnedDiffuseTexture
	};



	// Represents custom programmable rendering logic for 3D objects
	class Shader
	{
	public:

		//
		// Ctor / Dtor
		//

		// Create a new shader with file paths to the vertex and fragment shaders.
		// Do not call in the Game's constructor; OpenGL will freak out.
		Shader(const char* const vertexShaderPath, 
			   const char* const fragmentShaderPath,
			   ShaderName newName);
		
		// Dtor
		~Shader();



		//
		// Methods
		//

		// Make this shader the active shader
		void MakeActive();

		// Get the engine ID of this shader (this is not the OpenGL handle!)
		const unsigned int GetId() const;

		// Get an array (actually pointer) of shader uniforms for this shader.
		// Get the number of uniforms by calling GetNumberOfUniforms()
		ShaderUniformHandle* const GetUniforms() const;

		// How many uniforms does this shader have?
		const unsigned int GetNumberOfUniforms() const;

		// Setup a GpuBuffer as the input of the shader, only 1 at a time.
		// Activate VAO and shader first!
		void SetInputBuffer(GpuBuffer* const inputBuffer, const char* const nameInShader, const bool activate);



	private:

		//
		// Data
		//

		GLuint shaderProgram;
		ShaderUniformHandle* uniforms;
		unsigned int numberOfUniforms;
		ShaderName name;



		//
		// Static Data
		//

		static IdGenerator s_idGen;
		




		//
		// Private Routines
		//

		// Compiles a shader from file. Also calls CompileShaderNoLoad().
		bool CompileShader(GLuint& subshader, const char * const path, GLenum subshaderType);
		
		// Compiles a shader from memory buffer, not file.
		bool CompileShaderNoLoad(GLuint& subshader, const char * const source, GLenum subshaderType, const char * const shaderName);
		
		// Links a shader and checks for errors
		bool LinkShader(GLuint& program, GLuint& vs, GLuint& fs);
		
		// Replaces broken shaders with backup "error" shaders that are always supposed to work
		void UseErrorShader(GLuint& vs, GLuint& fs, bool deletePreviousShaders = true);





		//
		// Deleted Methods
		//

		// No default ctor
		Shader() = delete;
		
		// No copy assignment
		Shader& operator=(const Shader& other) = delete;

		// No copy ctor
		Shader(const Shader& other) = delete;

		// No move ctor
		Shader(Shader&& other) = delete;

		// No move assignment
		Shader& operator=(Shader&& other) = delete;

	};

	
}

#endif