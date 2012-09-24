#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec4 color;

out vec4 frag_color;

uniform mat4 MV;
uniform mat4 P;
uniform vec4 Fog_Color;

const float LOG2 = 1.442695;
const float FOG_CONSTANT = 0.02;
const float MIN_POINT_SIZE = 4.0;
const float MAX_POINT_SIZE = 120.0;
const float POINT_DISTANCE_MULT = 10.0;
const vec4  MAX_GLOW = vec4(180, 100, 50, 0);
const float GLOW_DISTANCE_MULT = 8.0;

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
	
	frag_color = mix(
		Fog_Color,
		color + clamp(MAX_GLOW - dist * GLOW_DISTANCE_MULT, vec4(0.0), vec4(255.0)),
		fogfac
	);
	
	vec4 v = vec4(vertex, 1.0);
	gl_Position = P * MV * v;
	gl_PointSize = clamp(MAX_POINT_SIZE - dist * POINT_DISTANCE_MULT, MIN_POINT_SIZE, MAX_POINT_SIZE);
}