#version 400 core

in float fog_amount;
in vec3 tex_coord;

layout(location = 0) out vec4 color;

uniform vec3 Fog_Color;
uniform sampler2D Texture_Sampler;
uniform sampler2DArray Texture_Array_Sampler;

void main()
{
	if(tex_coord.r < 0.0)
	{
		color = mix(
			vec4(Fog_Color, 1.0),
			texture(Texture_Sampler, tex_coord.st),
			fog_amount
		);
	} else
	{
		color = mix(
			vec4(Fog_Color, 1.0),
			texture(Texture_Array_Sampler, tex_coord),
			fog_amount
		);
	}
}