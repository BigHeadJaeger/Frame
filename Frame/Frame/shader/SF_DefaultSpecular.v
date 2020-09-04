#version 460

layout(location = 0) in vec3 positionL;
layout(location = 1) in vec3 normalL;
layout(location = 2) in vec2 texcoordV;

out vec3 positionW;
out vec3 normalW;
out vec2 texcoordF;

uniform mat4 world;
uniform mat4 worldViewProj;
uniform mat4 worldInvTranspose;

void main()
{
	positionW = (world * vec4(positionL, 1.0)).xyz;
	normalW = (worldInvTranspose * vec4(normalL, 1.0)).xyz;
	texcoordF = texcoordV;
	gl_Position = worldViewProj * vec4(positionL, 1.0);
}