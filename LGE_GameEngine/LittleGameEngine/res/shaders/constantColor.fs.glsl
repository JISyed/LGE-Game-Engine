#version 400 core

out vec4 color;

uniform vec4 tint_color = vec4(0.0, 1.0, 1.0, 1.0);

void main(void)
{
    color = tint_color;
}