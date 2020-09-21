#include "Texture.h"
#include"stb_image.h"

void Texture::LoadTexture(string path)
{
	filePath = path;
	glGenTextures(1, &id);					//生成一个纹理ID
	imgResult = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
	//imgResult = SOIL_load_image(path.c_str(), &width, &height, &numChannels, SOIL_LOAD_AUTO);

	// 先设置为默认属性
	DefaultTex2DSetting();
}

void Texture::LoadHDRTexture(string path)
{
	stbi_set_flip_vertically_on_load(true);		//将图片第一个像素设置为左下角开始
	int width, height, nrComponents;

}
