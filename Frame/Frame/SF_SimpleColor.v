#version 430

layout(location=0) in vec3 positionL;

uniform mat4 world;
uniform mat4 worldViewProj;
uniform mat4 worldInvTranspose;

void main()
{
	gl_Position=worldViewProj*vec4(VertexPosition,1.0);
}