#version 460

layout(location = 0) in vec3 positionL;
layout(location = 1) in vec3 normalL;
layout(location = 2) in vec2 texcoordL;
layout(location = 3) in vec4 vertexColor;

uniform mat4 world;
uniform mat4 worldViewProj;
uniform mat4 worldInvTranspose;

out vec4 fragmentColor;

void main()
{
	fragmentColor = vertexColor;
	gl_Position = worldViewProj * vec4(positionL, 1.0);
}
