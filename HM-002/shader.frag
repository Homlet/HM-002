#version 330 core

in vec3 frag_color;
in vec2 tex_coord;

layout(location = 0) out vec4 color;

uniform sampler2D Texture_Sampler;

void main()
{
	color = vec4(texture( Texture_Sampler, tex_coord ).rgb * frag_color, 1.0);
}