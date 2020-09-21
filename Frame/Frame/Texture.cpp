#include "Texture.h"
#include"stb_image.h"

void Texture::LoadTexture(string path)
{
	filePath = path;
	glGenTextures(1, &id);					//����һ������ID
	imgResult = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
	//imgResult = SOIL_load_image(path.c_str(), &width, &height, &numChannels, SOIL_LOAD_AUTO);

	// ������ΪĬ������
	DefaultTex2DSetting();
}

void Texture::LoadHDRTexture(string path)
{
	stbi_set_flip_vertically_on_load(true);		//��ͼƬ��һ����������Ϊ���½ǿ�ʼ
	int width, height, nrComponents;

}
