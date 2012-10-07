#version 400 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 uv;

out float fog_amount;
out vec3 tex_coord;

uniform mat4 MV;
uniform mat4 P;

const float LOG2 = 1.442695;
const float FOG_CONSTANT = 0.035;
const float MIN_POINT_SIZE = 4.0;
const float MAX_POINT_SIZE = 120.0;
const float POINT_DISTANCE_MULT = 10.0;

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

	fog_amount = clamp(fogfac, 0.0, 1.0);
	tex_coord = uv;
	
	vec4 v = vec4(vertex, 1.0);
	gl_Position = P * MV * v;
	gl_PointSize = max(MIN_POINT_SIZE, MAX_POINT_SIZE - dist * POINT_DISTANCE_MULT);
}