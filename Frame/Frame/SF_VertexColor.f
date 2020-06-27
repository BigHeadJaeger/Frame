#version 460

in vec4 fragmentColor;

out vec4 FragColor;

void main()
{
	FragColor = fragmentColor;
	//FragColor = vec4(255, 0, 0, 1);
}