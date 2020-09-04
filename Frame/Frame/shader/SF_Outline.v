#version 430
layout(location=0) in vec3 positionL;
uniform mat4 worldViewProj;

void main()
{
	gl_Position = worldViewProj * vec4(positionL, 1.0);
}