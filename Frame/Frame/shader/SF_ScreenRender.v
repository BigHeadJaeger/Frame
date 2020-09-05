#version 460

layout(location = 0) in vec3 positionL;
layout(location = 1) in vec2 texcoordV;

out vec2 texcoordF;

void main()
{
	// ��������ת��ֱ��������Ļ
	gl_Position = vec4(positionL.x, positionL.y,  0.0, 1.0);
	texcoordF = texcoordV;
}