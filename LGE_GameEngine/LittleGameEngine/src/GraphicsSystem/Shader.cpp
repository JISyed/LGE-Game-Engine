#include "Shader.h"
#include <cassert>
#include <cstdio>
#include "File.h"

#include "ErrorShaderHelper.h"
#include "ShaderUniformHandle.h"
#include "GpuBuffer.h"

namespace lge
{
	//
	// Static Data
	//

	IdGenerator Shader::s_idGen;




	//
	// Methods
	//

	// Create a new shader with file paths to the vertex and fragment shaders.
	// Do not call in the Game's constructor; OpenGL will freak out
	Shader::Shader(const char* const vertexShaderPath, 
				   const char* const fragmentShaderPath,
				   ShaderName newName) :
		//ID(s_idGen.MakeNewId()),
		shaderProgram(400000000u),
		name(newName)
	{
		// Vert file name must be valid
		assert(vertexShaderPath != nullptr);
		// Frag file name must be valid
		assert(fragmentShaderPath != nullptr);

		// Create a new shader for OpenGL
		this->shaderProgram = glCreateProgram();
		
		// Load the vertex portion of the shader and compile it
		GLuint vs;
		bool vertFailed = false;
		vertFailed = !this->CompileShader(vs, vertexShaderPath, GL_VERTEX_SHADER);

		// Load the fragment portion of the shader and compile it
		GLuint fs;
		bool fragFailed = false;
		fragFailed = !this->CompileShader(fs, fragmentShaderPath, GL_FRAGMENT_SHADER);


		// If shaders failed, load alternative "error" shaders
		if (vertFailed || fragFailed)
		{
			this->UseErrorShader(vs, fs);
		}


		// Link the shader
		bool linkSuccess = this->LinkShader(this->shaderProgram, vs, fs);
		if (!linkSuccess)
		{
			// If the linker fails, use our error shaders instead
			glDetachShader(this->shaderProgram, vs);
			glDetachShader(this->shaderProgram, fs);
			this->UseErrorShader(vs, fs);
			linkSuccess = this->LinkShader(this->shaderProgram, vs, fs);
		}
		assert(linkSuccess);


		// Shaders can be deleted after linking to free graphics memory
		glDeleteShader(vs);
		glDeleteShader(fs);


		


		// Setup internal array of uniforms ...

		// Get the total number of uniforms in the shader (includes Sampler2D and SamplerCube)
		int numOfShaderUniforms = -1;
		glGetProgramiv(this->shaderProgram, GL_ACTIVE_UNIFORMS, &numOfShaderUniforms);
		const unsigned int totalUniforms = (unsigned int)numOfShaderUniforms;
		this->numberOfUniforms = totalUniforms;

		// Make the array allocation for the uniform handles
		this->uniforms = new ShaderUniformHandle[totalUniforms];

		// Make every uniform handle
		for (unsigned int i = 0; i < totalUniforms; i++)
		{
			// Uniform metadata
			GLsizei uniformNameLen = -1;
			int sizeOfUniform = -1;			// Actually number of elements. Usually 1, unless it's an array
			GLenum uniformDataType = GL_ZERO;
			char uniformArrayName[LGE_MAX_UNIFORM_NAME_LEN];
			
			// Quering metadata
			glGetActiveUniform(this->shaderProgram,				// Shader Program
							   i,								// Current Uniform Location
							   LGE_MAX_UNIFORM_NAME_LEN - 1,	// Max uniform name length
							   &uniformNameLen,					// Actual length of uniform name (excluding '\0')
							   &sizeOfUniform,					// Size of the uniform variable
							   &uniformDataType,				// Data type of the uniform
							   uniformArrayName					// Actual uniform name (as char array)
			);
			
			// Null-terminate string, just in case
			uniformArrayName[uniformNameLen] = '\0';

			// Make sure our uniform locations are in line (probably better in debug only)
			GLuint location = glGetUniformLocation(this->shaderProgram, uniformArrayName);
			//assert(location == i);	// EDIT: They probably shouldn't coorespond
			

			// Use metadata to make a uniform handle object
			UniformName uniformName = UniformNameHelper::GetUniformNameFromString(uniformArrayName);
			UniformType uniformType = UniformType::Float;	// Doesn't matter that the inital value is
			if (sizeOfUniform > 1 && uniformDataType == GL_FLOAT_MAT4)
			{
				uniformType = UniformType::Matrix4x4Array;
			}
			else
			{
				uniformType = UniformNameHelper::GetUniformTypeFromGlenum(uniformDataType);
			}
			this->uniforms[i] = ShaderUniformHandle(uniformName, uniformType, location);
		}


	}


	// Dtor
	Shader::~Shader()
	{
		glDeleteProgram(this->shaderProgram);

		delete[] this->uniforms;
		this->uniforms = nullptr;
	}



	// Make this shader the active shader
	void Shader::MakeActive()
	{
		glUseProgram(this->shaderProgram);
	}


	// Get the engine ID of this shader (this is not the OpenGL handle!)
	const unsigned int Shader::GetId() const
	{
		//return this->ID;
		return static_cast<unsigned int>(this->name);
	}





	// Get an array (actually pointer) of shader uniforms for this shader.
	// Get the number of unifomrs by calling GetNumberOfUniforms()
	ShaderUniformHandle* const Shader::GetUniforms() const
	{
		return this->uniforms;
	}


	// How many uniforms does this shader have?
	const unsigned int Shader::GetNumberOfUniforms() const
	{
		return this->numberOfUniforms;
	}



	// Setup a GpuBuffer as the input of the shader, only 1 at a time.
	void Shader::SetInputBuffer(GpuBuffer* const inputBuffer, const char* const nameInShader, const bool activate)
	{
		if (activate)
		{
			inputBuffer->ActivateAs(GpuBufferType::UniformBuffer);
		}
		const GLuint handleInShader = glGetUniformBlockIndex(this->shaderProgram, nameInShader);
		assert(handleInShader != GL_INVALID_INDEX);
		glUniformBlockBinding(this->shaderProgram, handleInShader, 0);
		inputBuffer->PrepareAsUniformInput();
		assert(glGetError() == GL_NO_ERROR);
	}







	//
	// Private Routines
	//


	// Compiles a shader from file. Also calls CompileShaderNoLoad().
	bool Shader::CompileShader(GLuint& subshader, const char * const path, GLenum subshaderType)
	{
		// Path has to be valid
		assert(path != nullptr);

		// Load the Shader ---------

		FileHandle fh;
		FileError  fileErrorCode;



		// Open the shader file
		fileErrorCode = File::open(fh, path, FileMode::FILE_READ, true);
		assert(fileErrorCode == FileError::FILE_SUCCESS);
		if (fileErrorCode != FileError::FILE_SUCCESS)
		{
			return false;
		}




		// Get the size of the file
		fileErrorCode = File::seek(fh, FileSeek::FILE_SEEK_END, 0);
		assert(fileErrorCode == FileError::FILE_SUCCESS);
		if (fileErrorCode != FileError::FILE_SUCCESS)
		{
			return false;
		}
		int numBytesInFile;
		fileErrorCode = File::tell(fh, numBytesInFile);
		assert(fileErrorCode == FileError::FILE_SUCCESS);
		if (fileErrorCode != FileError::FILE_SUCCESS)
		{
			return false;
		}
		fileErrorCode = File::seek(fh, FileSeek::FILE_SEEK_BEGIN, 0);
		assert(fileErrorCode == FileError::FILE_SUCCESS);
		if (fileErrorCode != FileError::FILE_SUCCESS)
		{
			return false;
		}



		// Read the file into memory
		char *source = new char[numBytesInFile + 1];
		assert(source != 0);
		if (source == 0)
		{
			return false;
		}
		fileErrorCode = File::read(fh, source, numBytesInFile);
		assert(fileErrorCode == FileError::FILE_SUCCESS);
		if (fileErrorCode != FileError::FILE_SUCCESS)
		{
			return false;
		}
		// null termination character
		source[numBytesInFile] = 0;



		// Close the file
		fileErrorCode = File::close(fh);
		assert(fileErrorCode == FileError::FILE_SUCCESS);
		if (fileErrorCode != FileError::FILE_SUCCESS)
		{
			return false;
		}




		// Compile the Shader ------
		return this->CompileShaderNoLoad(subshader, source, subshaderType, path);

	}



	// Compiles a shader from memory buffer, not file.
	bool Shader::CompileShaderNoLoad(GLuint& subshader, const char * const source, GLenum subshaderType, const char * const shaderName)
	{
		// Shader source must be valid
		assert(source != nullptr);
		// Name string must be valid
		assert(shaderName != nullptr);

		// Compile the Shader ------
		subshader = glCreateShader(subshaderType);
		glShaderSource(subshader, 1, &source, NULL);
		glCompileShader(subshader);

		// Check for errors in our shader
		GLint errorCode = 0;
		glGetShaderiv(subshader, GL_COMPILE_STATUS, &errorCode);

		// Complain on error
		if (!errorCode)
		{
			// Get error message from OpenGL
			char errorMessage[4096];
			glGetShaderInfoLog(subshader, 4096, NULL, errorMessage);

			printf("Error Compiling Shader \"%s\": %s\n", shaderName, errorMessage);
			
			// Freak out (about compile error)
			assert(errorCode);
			return false;
		}

		// Success
		return true;
	}



	// Replaces broken shaders with backup "error" shaders that are always supposed to work
	void Shader::UseErrorShader(GLuint& vs, GLuint& fs, bool deletePreviousShaders)
	{
		if (deletePreviousShaders)
		{
			// Delete previous shaders
			glDeleteShader(vs);
			glDeleteShader(fs);
		}

		bool vertFailed = !this->CompileShaderNoLoad(vs,
												ErrorShaderHelper::GetVertexSource(),
												GL_VERTEX_SHADER,
												"ErrorVertexShader");

		// If our error shaders fail, we should fix them
		assert(!vertFailed); vertFailed;

		bool fragFailed = !this->CompileShaderNoLoad(fs,
												ErrorShaderHelper::GetFragmentSource(),
												GL_FRAGMENT_SHADER,
												"ErrorFragmentShader");

		// If our error shaders fail, we should fix them
		assert(!fragFailed); fragFailed;
	}



	// Links a shader and checks for errors
	bool Shader::LinkShader(GLuint& program, GLuint& vs, GLuint& fs)
	{
		// Attach our vertex and fragment render procedures into our shader
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		
		// Make sure our shader as a whole works
		glLinkProgram(program);

		// Check linker errors
		GLint linkerSuccess = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &linkerSuccess);
		if (linkerSuccess == GL_FALSE)
		{
			// Get error message for linker
			GLchar errorMessage[4096] = {0};
			glGetProgramInfoLog(program, 4096, NULL, errorMessage);
			printf("Error Linking Shader: %s\n", errorMessage);
			
			// Freak out (on linker errors)
			assert(linkerSuccess);
			return false;
		}

		// Success
		return true;
	}


}