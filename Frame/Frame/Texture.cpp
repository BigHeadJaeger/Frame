#include "Texture.h"

void Texture::LoadTexture(string path)
{
	filePath = path;
	glGenTextures(1, &id);					//����һ������ID
	imgResult = SOIL_load_image(path.c_str(), &width, &height, &numChannels, SOIL_LOAD_AUTO);

	// ������ΪĬ������
	DefaultTex2DSetting();
}
