#version 400 core

layout (location = 0) in vec4 translation;
layout (location = 1) in vec4 rotation;
layout (location = 2) in vec4 scale;

out mat4 matrix;

void main(void)
{
	mat4 t = mat4(1.0);
	t[3] = translation;
	//t = transpose(t);

	float xx = rotation.x * rotation.x;
	float xy = rotation.x * rotation.y;
	float xz = rotation.x * rotation.z;
	float xw = rotation.x * rotation.w;
	float yy = rotation.y * rotation.y;
	float yz = rotation.y * rotation.z;
	float yw = rotation.y * rotation.w;
	float zz = rotation.z * rotation.z;
	float zw = rotation.z * rotation.w;

	mat4 r = mat4(1.0);
	r[0] = vec4(1.0 - 2.0 * (yy + zz), 2.0 * (xy + zw), 2.0 * (xz - yw), 0.0);
	r[1] = vec4(2.0 * (xy - zw), 1.0 - 2.0 * (xx + zz), 2.0 * (yz + xw), 0.0);
	r[2] = vec4(2.0 * (xz + yw), 2.0 * (yz - xw), 1.0 - 2.0 * (xx + yy), 0.0);

	mat4 s = mat4(1.0);
	s[0][0] = scale.x;
	s[1][1] = scale.y;
	s[2][2] = scale.z;

	matrix = t * r * s;
}
