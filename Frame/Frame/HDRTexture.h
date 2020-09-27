#pragma once
#include<string>
#include<glad/glad.h>
#include<iostream>

#include"stb_image.h"

using namespace std;

class HDRTexture
{
private:
	GLuint id;
	string filePath;

	int width;
	int height;
	int numChannels;

	float* HDRData;
public:
	void LoadHDRTexture(string path)
	{
		stbi_set_flip_vertically_on_load(true);		//将图片第一个像素设置为左下角开始
		HDRData = stbi_loadf(path.c_str(), &width, &height, &numChannels, 0);
		if (HDRData)
		{
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, HDRData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(HDRData);
		}
		else
			cout << "Load HDR Texture failed" << endl;
	}
};