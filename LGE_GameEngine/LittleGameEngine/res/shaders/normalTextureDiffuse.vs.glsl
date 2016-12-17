#version 400
//http://www.geeks3d.com/20130122/normal-mapping-without-precomputed-tangent-space-vectors/

// Per-vertex inputs
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normal;

// Uniforms we'll need
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform vec4 light_pos;

// Varying variables
out VS_OUT
{
	vec4 normals;
	vec2 texCoords;
	vec4 lightDir;
	vec4 eyeDir;
} vout;
 
 
void main()
{
  gl_Position = proj_matrix * view_matrix * model_matrix * position;
  
  vout.texCoords = uvs;
  vout.normals = view_matrix * model_matrix  * vec4(normal, 0.0);
  
  vec4 view_vertex = view_matrix * model_matrix * position;
  vout.lightDir = light_pos - view_vertex;;
  vout.eyeDir = -view_vertex;
  
}