#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec4 color;

out vec4 frag_color;

uniform mat4 MVP;

void main()
{
	frag_color = color;
	
	vec4 v = vec4(vertex, 1.0);
	gl_Position = MVP * v;
}