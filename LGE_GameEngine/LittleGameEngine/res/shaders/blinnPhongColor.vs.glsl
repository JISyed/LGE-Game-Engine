#version 400 core

// Per-vertex inputs
layout (location = 0) in vec4 position;
layout (location = 2) in vec3 normal;

// Matrices we'll need
//layout (std140) uniform constants
//{
   uniform mat4 model_matrix;
   uniform mat4 view_matrix;
   uniform mat4 proj_matrix;
//};

// Inputs from vertex shader
out VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
} vs_out;

// Position of light
uniform vec4 light_pos = vec4(0.0, 0.0, 0.0, 1.0);

void main(void)
{
    // Calculate view-space coordinate
    vec4 P = view_matrix * model_matrix * position;

    // Calculate normal in view-space
    vs_out.N = mat3(view_matrix) * mat3(model_matrix) * normal;

    // Calculate light vector
	vec4 transformedLight = light_pos;
    vs_out.L = transformedLight.xyz - P.xyz;

    // Calculate view vector
    vs_out.V = -P.xyz;

    // Calculate the clip-space position of each vertex
    gl_Position = proj_matrix * P;
}
