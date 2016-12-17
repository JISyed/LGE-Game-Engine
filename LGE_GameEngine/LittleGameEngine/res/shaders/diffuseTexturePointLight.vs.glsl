#version 400 core

// Uniforms
	uniform mat4 model_matrix;
	uniform mat4 view_matrix;
	uniform mat4 proj_matrix;
	uniform vec4 light_pos;
	uniform vec4 light_color;

// Attributes
	layout (location = 0) in vec4 vPosition;
	layout (location = 1) in vec2 vTexCoord0;
	layout (location = 2) in vec3 vNormal;

// Varying
	out VS_OUT
	{
		vec4 vFragColor;
		vec2 vTex;
	} vs_out;


void main(void) 
{ 
	// Get vNorm
		mat4 mvMatrix = view_matrix * model_matrix;
		mat3 mNormalMatrix;
		mNormalMatrix[0] = normalize(mvMatrix[0].xyz);
		mNormalMatrix[1] = normalize(mvMatrix[1].xyz);
		mNormalMatrix[2] = normalize(mvMatrix[2].xyz);
		vec3 vNorm = normalize(mNormalMatrix * vNormal);

	// Get vLightDir
		vec4 ecPosition;
		vec3 ecPosition3;
		ecPosition = mvMatrix * vPosition;
		ecPosition3 = ecPosition.xyz /ecPosition.w;
		vec4 transformedLight = light_pos;
		vec3 vLightDir = normalize(transformedLight.xyz - ecPosition3);

	// Get vFragColor
		float fDot = max(0.0, dot(vNorm, vLightDir)); 
		vs_out.vFragColor.rgb = light_color.rgb * fDot;
		vs_out.vFragColor.a = light_color.a;

	// Get vTex;
		vs_out.vTex = vTexCoord0;

	// Set Gl_position
		gl_Position = proj_matrix * view_matrix * model_matrix * vPosition;
}