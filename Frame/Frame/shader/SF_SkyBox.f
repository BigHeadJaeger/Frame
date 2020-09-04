#version 460

in vec3 texcoordF;

out vec4 FragColor;

uniform samplerCube cubemap;

void main()
{
	FragColor = texture(cubemap, texcoordF);
	//FragColor = vec4(1,0,0,1);
}