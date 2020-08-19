#version 460

layout(location=0) in vec3 positionL;
layout(location=1) in vec3 normalL;

out vec3 posW;					// ���ռ�����Ҫ�������������
out vec3 normalW;				// ���㷨��������������

uniform mat4 world;
uniform mat4 worldViewProj;
uniform mat4 worldInvTranspose;

uniform vec3 eyePos;

void main()
{
	posW = (world * vec4(positionL, 1.0)).xyz;
	normalW = (worldInvTranspose * vec4(normalL, 1.0)).xyz;
	gl_Position = worldViewProj * vec4(positionL, 1.0);
}

