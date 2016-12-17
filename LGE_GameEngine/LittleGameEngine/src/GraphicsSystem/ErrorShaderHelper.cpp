#include "ErrorShaderHelper.h"

namespace lge
{
	// The working vertex shader if our custom shader fails
	static const char * const vs_source[] =
	{
		"#version 400 core                                                      \n"
		"                                                                       \n"
		"in vec4 position;                                                      \n"
		"                                                                       \n"
		"out VS_OUT                                                             \n"
		"{                                                                      \n"
		"    vec4 color;                                                        \n"
		"} vs_out;                                                              \n"
		"                                                                       \n"
		"uniform mat4 model_matrix;                                             \n"
		"uniform mat4 view_matrix;                                              \n"
		"uniform mat4 proj_matrix;                                              \n"
		"                                                                       \n"
		"void main(void)                                                        \n"
		"{                                                                      \n"
		"    gl_Position = proj_matrix * view_matrix * model_matrix * position; \n"
		"    vs_out.color = vec4(1.0, 0.0, 1.0, 1.0);                           \n"
		"}                                                                      \n"
	};

	// The working fragment shader if our custom shader fails (colors magenta)
	static const char * const fs_source[] =
	{
		"#version 400 core                                                  \n"
		"                                                                   \n"
		"out vec4 color;                                                    \n"
		"                                                                   \n"
		"in VS_OUT                                                          \n"
		"{                                                                  \n"
		"    vec4 color;                                                    \n"
		"} fs_in;                                                           \n"
		"                                                                   \n"
		"void main(void)                                                    \n"
		"{                                                                  \n"
		"    color = fs_in.color;                                           \n"
		"}                                                                  \n"
	};

	
	const char* const ErrorShaderHelper::GetVertexSource()
	{
		return *vs_source;
	}

	const char* const ErrorShaderHelper::GetFragmentSource()
	{
		return *fs_source;
	}
}