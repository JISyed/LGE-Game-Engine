#version 400 core

// Not allowed in 400, only 420
// layout (binding = 0) uniform sampler2D color_map;

uniform sampler2D color_map;

in VS_OUT
{
    vec2 textCoordinate;
} fs_in;

out vec4 color;

void main(void)
{
    color = texture(color_map, fs_in.textCoordinate );
}
