#version 400 core

uniform mat4 modelMat;

uniform ParentsBlock
{
	mat4 local[100];
} Parents;

layout (location = 0) in uvec4 index0;
layout (location = 1) in uvec4 index1;
layout (location = 2) in uvec4 index2;
layout (location = 3) in uvec4 index3;

out mat4 global;


void main(void)
{
	global = modelMat * Parents.local[1] * // root
			  Parents.local[index3[3]] * Parents.local[index3[2]] * Parents.local[index3[1]] * Parents.local[index3[0]] *
			  Parents.local[index2[3]] * Parents.local[index2[2]] * Parents.local[index2[1]] * Parents.local[index2[0]] *
			  Parents.local[index1[3]] * Parents.local[index1[2]] * Parents.local[index1[1]] * Parents.local[index1[0]] *
			  Parents.local[index0[3]] * Parents.local[index0[2]] * Parents.local[index0[1]] * Parents.local[index0[0]];
}
