#version 400 core

in vec4 position;

out VS_OUT
{
    vec4 color;
} vs_out;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

void main(void)
{ 
    gl_Position = proj_matrix * view_matrix * model_matrix * position; 
    vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}