#ifndef LGE_ERROR_SHADER_HELPER_H
#define LGE_ERROR_SHADER_HELPER_H

namespace lge
{
	// Utility class to load a hard-coded "error" shader if shaders fail to load
	class ErrorShaderHelper
	{
	public:

		//
		// Methods
		//

		// Get the vertex shader code for the error shader
		static const char* const GetVertexSource();

		// Get the fragment shader code for the error shader
		static const char* const GetFragmentSource();




	private:

		//
		// Deleted Methods
		//

		ErrorShaderHelper() = delete;
		~ErrorShaderHelper() = delete;
		ErrorShaderHelper(const ErrorShaderHelper& other) = delete;
		ErrorShaderHelper& operator=(const ErrorShaderHelper& other) = delete;
		ErrorShaderHelper(ErrorShaderHelper&& other) = delete;
		ErrorShaderHelper& operator=(ErrorShaderHelper&& other) = delete;
	};
}

#endif