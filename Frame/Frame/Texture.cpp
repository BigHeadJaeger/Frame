#include "Texture.h"

void Texture::LoadTexture(string path)
{
	filePath = path;
	glGenTextures(1, &id);					//生成一个纹理ID
	imgResult = SOIL_load_image(path.c_str(), &width, &height, &numChannels, SOIL_LOAD_AUTO);

	// 先设置为默认属性
	DefaultTex2DSetting();
}
