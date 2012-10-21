#version 400 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 str;

out float fog_amount;
out vec3 tex_coord;

uniform mat4 MV;
uniform mat4 P;

#define LOG2 1.442695
#define FOG_CONSTANT 0.1
#define FOG_START_DISTANCE 10
#define MIN_POINT_SIZE 4.0
#define MAX_POINT_SIZE 20.0
#define POINT_DISTANCE_MULT 10.0

void main()
{
	vec4 v = vec4(vertex, 1.0);
	v = MV * v;

	float dist = max(length(v) - FOG_START_DISTANCE, 0);
	float fogfac = exp2(
		-FOG_CONSTANT *
		FOG_CONSTANT *
		dist *
		dist *
		LOG2
	);

	fog_amount = clamp(fogfac, 0.0, 1.0);
	tex_coord = str;
	
	gl_Position = P * v;
	gl_PointSize = max(MIN_POINT_SIZE, MAX_POINT_SIZE - dist * POINT_DISTANCE_MULT);
}