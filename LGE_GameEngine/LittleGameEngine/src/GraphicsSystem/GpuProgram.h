#ifndef H_LGE_GPU_PROGRAM
#define H_LGE_GPU_PROGRAM

#include "GL\gl3w.h"

namespace lge
{
	// Forward declare
	class GpuBuffer;
	class Matrix;


	// TEMP: Find a better way to dynamically name GPU programs
	enum class GpuProgramName : unsigned int
	{
		AnimFrameMixer,
		AnimJointToLocalMatrix,
		AnimLocalToWorldMatrix
	};


	class GpuProgram
	{
	public:

		//
		// Ctor / Dtor
		//
		GpuProgram(const char* const programShaderPath, const GpuProgramName newName, const int numberOfOutputs, const GLchar*const * outputNames);
		~GpuProgram();


		//
		// Methods
		//

		// Get the name of this GPU program
		const GpuProgramName GetName();

		// Make this GpuProgram the active program (affects GpuPrograms and Shaders)
		void MakeActive();

		// Setup a GpuBuffer as the input of the program, only 1 at a time.
		// Activate VAO and program first!
		void SetInputBuffer(GpuBuffer* const inputBuffer, const char* const nameInShader);

		// Execute program and write output into the given GpuBuffer.
		// Activate VAO and program first!
		void Execute(GpuBuffer* const outputBuffer);

		// Execute program and write output into a range of the given GpuBuffer.
		// Activate VAO and program first!
		void ExecuteRange(GpuBuffer* const outputBuffer, const size_t startingElement, const size_t endingElement);

		// Setup the input buffer format for this program
		// Activate VAO and program first!
		// Also activate corresponding GpuBuffer prior to calling for performance reasons
		void FormatInputBufferInt(const char* const attributeNameInShader, const size_t attribVectorSize, const size_t strideSize, const size_t offset);

		// Setup the input buffer format for this program
		// Activate VAO and program first!
		// Also activate corresponding GpuBuffer prior to calling for performance reasons
		void FormatInputBufferFloat(const char* const attributeNameInShader, const size_t attribVectorSize, const size_t strideSize, const size_t offset);



		//
		// Uniform setters
		//

		// Set a single float value in the GPU program given the variable name in the program
		void SetUniform(const char* const nameInProgram, const float value);

		// Set a matrix value in the GPU program givene the variable name in the program
		void SetUniform(const char* const nameInProgram, const Matrix& value);


	private:

		//
		// Data
		//

		GLuint programHandle;	// OpenGL shader program handle
		GpuProgramName name;	// Name of the program



		//
		// Private Routines
		//

		// Compiles a program shader from file. Also calls CompileShaderNoLoad().
		bool CompileShader(GLuint& shaderId, const char * const path);

		// Compiles a program shader from memory buffer, not file.
		bool CompileShaderNoLoad(GLuint& shaderId, const char * const source);

		// Link the program shader
		bool LinkShader();


		//
		// Deleted Methods
		//

		// No default ctor
		GpuProgram() = delete;

		// No copy assignment
		GpuProgram& operator=(const GpuProgram& other) = delete;

		// No copy ctor
		GpuProgram(const GpuProgram& other) = delete;

		// No move ctor
		GpuProgram(GpuProgram&& other) = delete;

		// No move assignment
		GpuProgram& operator=(GpuProgram&& other) = delete;

	};
}
#endif