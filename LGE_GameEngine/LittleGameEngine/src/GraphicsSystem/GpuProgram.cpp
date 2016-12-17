#include "GpuProgram.h"
#include <cassert>
#include "File.h"
#include <cstdio>
#include "GpuBuffer.h"

namespace lge
{
	GpuProgram::GpuProgram(const char* const programShaderPath, const GpuProgramName newName, const int numberOfOutputs, const GLchar*const * outputNames) :
		name(newName)
	{
		// GpuProgram source path must be valid
		assert(programShaderPath != nullptr);

		// Load the GPU program source and compile it
		GLuint ps;
		bool sourceFailed = false;
		sourceFailed = !this->CompileShader(ps, programShaderPath);
		assert(!sourceFailed);

		// Create a program handle into OpenGL (it's basically a shader)
		this->programHandle = glCreateProgram();
		glAttachShader(this->programHandle, ps);

		// Declare the output shader variables of the GPU program
		glTransformFeedbackVaryings(this->programHandle, numberOfOutputs, outputNames, GL_INTERLEAVED_ATTRIBS);

		// Link the program
		bool linkSucess = this->LinkShader();
		assert(linkSucess); linkSucess;

		// Shaders can be deleted after linking to free graphics memory
		glDeleteShader(ps);
	}

	GpuProgram::~GpuProgram()
	{
		glDeleteProgram(this->programHandle);
		glUseProgram(0);
	}



	// Get the name of this GPU program
	const GpuProgramName GpuProgram::GetName()
	{
		return this->name;
	}


	// Make this GpuProgram the active program (affects GpuPrograms and Shaders)
	void GpuProgram::MakeActive()
	{
		glUseProgram(this->programHandle);
	}


	// Setup a GpuBuffer as the input of the program, only 1 at a time
	void GpuProgram::SetInputBuffer(GpuBuffer* const buffer, const char* const nameInShader)
	{
		buffer->ActivateAs(GpuBufferType::UniformBuffer);
		const GLuint handleInShader = glGetUniformBlockIndex(this->programHandle, nameInShader);
		assert(handleInShader != GL_INVALID_INDEX);
		glUniformBlockBinding(this->programHandle, handleInShader, 0);
		buffer->PrepareAsUniformInput();
		assert(glGetError() == GL_NO_ERROR);
	}


	// Execute program and write output into given GpuBuffer.
	void GpuProgram::Execute(GpuBuffer* const outputBuffer)
	{
		glEnable(GL_RASTERIZER_DISCARD);
		{
			outputBuffer->PrepareAsOutput();
			glBeginTransformFeedback(GL_POINTS);
			{
				glDrawArrays(GL_POINTS, 0, outputBuffer->GetNumberOfElements() * outputBuffer->GetElementSize());
			}
			glEndTransformFeedback();
		}
		glDisable(GL_RASTERIZER_DISCARD);
		glFlush();
	}


	// Execute program and write output into a range of the given GpuBuffer.
	void GpuProgram::ExecuteRange(GpuBuffer* const outputBuffer, const size_t startingElement, const size_t endingElement)
	{
		glEnable(GL_RASTERIZER_DISCARD);
		{
			const size_t range = outputBuffer->PrepareRangeAsOutput(startingElement, endingElement);
			assert(range <= outputBuffer->GetNumberOfElements());
			glBeginTransformFeedback(GL_POINTS);
			{
				glDrawArrays(GL_POINTS, 0, range * outputBuffer->GetElementSize());
			}
			glEndTransformFeedback();
		}
		glDisable(GL_RASTERIZER_DISCARD);
		glFlush();
	}



	// Setup the input buffer format for this program
	// Activate VAO and program first!
	// Also activate corresponding GpuBuffer prior to calling for performance reasons
	void GpuProgram::FormatInputBufferInt(const char* const attributeNameInShader, const size_t attribVectorSize, const size_t strideSize, const size_t offset)
	{
		const GLuint attribId = glGetAttribLocation(this->programHandle, attributeNameInShader);
		assert(attribId >= 0);
		glVertexAttribIPointer(attribId, attribVectorSize, GL_UNSIGNED_INT, strideSize, reinterpret_cast<void*>(offset));
		glEnableVertexAttribArray(attribId);
	}

	// Setup the input buffer format for this program
	// Activate VAO and program first!
	// Also activate corresponding GpuBuffer prior to calling for performance reasons
	void GpuProgram::FormatInputBufferFloat(const char* const attributeNameInShader, const size_t attribVectorSize, const size_t strideSize, const size_t offset)
	{
		const GLint attribId = glGetAttribLocation(this->programHandle, attributeNameInShader);
		assert(attribId >= 0);
		glVertexAttribPointer(attribId, attribVectorSize, GL_FLOAT, GL_FALSE, strideSize, reinterpret_cast<void*>(offset));
		glEnableVertexAttribArray(attribId);
	}




	// Set a single float value in the GPU program given the variable name in the program
	void GpuProgram::SetUniform(const char* const nameInProgram, const float value)
	{
		const GLint loc = glGetUniformLocation(this->programHandle, nameInProgram);
		glUniform1f(loc, value);
	}

	// Set a matrix value in the GPU program givene the variable name in the program
	void GpuProgram::SetUniform(const char* const nameInProgram, const Matrix& value)
	{
		const GLint loc = glGetUniformLocation(this->programHandle, nameInProgram);
		glUniformMatrix4fv(loc, 1, GL_FALSE, (const float *)&value);
	}





	//
	// Private
	//

	// Compiles a shader from file. Also calls CompileShaderNoLoad().
	bool GpuProgram::CompileShader(GLuint& shaderId, const char * const path)
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
		return this->CompileShaderNoLoad(shaderId, source);
	}


	// Compiles a shader from memory buffer, not file.
	bool GpuProgram::CompileShaderNoLoad(GLuint& shaderId, const char * const source)
	{
		// Shader source must be valid
		assert(source != nullptr);

		// Compile the Shader ------
		shaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shaderId, 1, &source, NULL);
		glCompileShader(shaderId);

		// Check for errors in our shader
		GLint errorCode = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &errorCode);

		// Complain on error
		if (!errorCode)
		{
			// Get error message from OpenGL
			char errorMessage[4096];
			glGetShaderInfoLog(shaderId, 4096, NULL, errorMessage);

			printf("Error Compiling GPU Program: %s\n", errorMessage);

			// Freak out (about compile error)
			assert(errorCode);
			return false;
		}

		// Success
		return true;
	}


	// Link the program shader
	bool GpuProgram::LinkShader()
	{
		// Make sure our shader as a whole works
		glLinkProgram(this->programHandle);

		// Check linker errors
		GLint linkerSuccess = GL_FALSE;
		glGetProgramiv(this->programHandle, GL_LINK_STATUS, &linkerSuccess);
		if (linkerSuccess == GL_FALSE)
		{
			// Get error message for linker
			GLchar errorMessage[4096] = {0};
			glGetProgramInfoLog(this->programHandle, 4096, NULL, errorMessage);
			printf("Error Linking GPU Program: %s\n", errorMessage);

			// Freak out (on linker errors)
			assert(linkerSuccess);
			return false;
		}

		// Success
		return true;
	}

}