#version 410 core

layout (location = 0) in vec2 position;

uniform mat4 projView;
uniform mat4 model;

void main()
{
	gl_Position =  projView * model * vec4(position, 0.0, 1.0);
}