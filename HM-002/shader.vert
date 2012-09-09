#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec4 color;

out vec4 frag_color;

uniform mat4 MV;
uniform mat4 P;
uniform vec4 Fog_Color;

const float LOG2 = 1.442695;
const float FOG_CONSTANT = 0.02;

void main()
{
	float dist = length(MV * vec4(vertex, 1.0));
	float fogfac = exp2(
		-FOG_CONSTANT *
		FOG_CONSTANT *
		dist *
		dist *
		LOG2
	);

	fogfac = clamp(fogfac, 0.0, 1.0);
	
	frag_color = mix(Fog_Color, color, fogfac);
	
	vec4 v = vec4(vertex, 1.0);
	gl_Position = P * MV * v;
}