#version 400 core

in float fog_amount;
in vec2 tex_coord;

layout(location = 0) out vec4 color;

uniform vec3 Fog_Color;
uniform sampler2D Texture_Sampler;

void main()
{
	color = mix(
		vec4(Fog_Color, 1.0f),
		texture(Texture_Sampler, tex_coord),
		fog_amount
	);
}