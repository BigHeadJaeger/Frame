#pragma once
#include"Texture.h"



class Texture2D : public Texture
{
private:
	Size2D size;
public:
	Texture2D(int _width = 256, int _height = 256)
	{
		size = Size2D(_width, _height);

		type = GL_TEXTURE_2D;

		warpSMode = GL_REPEAT;
		warpTMode = GL_REPEAT;
		minFilter = GL_LINEAR;
		magFilter = GL_LINEAR;
		isMipmap = true;

		pixelFormat = GL_RGB;
		channelFormat = GL_RGB;
		dataFormat = GL_UNSIGNED_BYTE;

		// 生成纹理
		glGenTextures(1, &id);
		glBindTexture(type, id);
		glTexParameteri(type, GL_TEXTURE_WRAP_S, warpSMode);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, warpTMode);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);

		glTexImage2D(type, 0, channelFormat, size.width, size.height, 0, pixelFormat, dataFormat, nullptr);
		if (isMipmap)
			glGenerateMipmap(type);

		glBindTexture(type, 0);
	}


	// 通过尺寸创建空纹理
	//void Create(int _width, int _height, GLuint _channelFormat = GL_RGB, GLenum _pixelFormat = GL_RGB, GLenum _dataFormat = GL_UNSIGNED_BYTE, bool _isMipMap = true)
	//{
	//	width = _width;
	//	height = _height;
	//	channelFormat = _channelFormat;
	//	pixelFormat = _pixelFormat;
	//	isMipmap = _isMipMap;
	//	glBindTexture(type, id);
	//	glTexImage2D(type, 0, channelFormat, width, height, 0, pixelFormat, dataFormat, nullptr);
	//	if (isMipmap)
	//		glGenerateMipmap(type);
	//	
	//	glBindTexture(type, 0);
	//}

	bool CreateFromImage(string path) override
	{
		unsigned char* imgResult;
		glGenTextures(1, &id);					//生成一个纹理ID
		imgResult = stbi_load(path.c_str(), &size.width, &size.height, &numChannels, 0);

		if (!imgResult)
		{
			cout << "load texture failed" << endl;
			return false;
		}

		if (numChannels == 1)
		{
			pixelFormat = GL_RED;
			channelFormat = GL_RED;
		}
		else if (numChannels == 3)
		{
			pixelFormat = GL_RGB;
			channelFormat = GL_RGB;
		}
		else if (numChannels == 4)
		{
			pixelFormat = GL_RGBA;
			channelFormat = GL_RGBA;
			warpSMode = GL_CLAMP_TO_EDGE;
			warpTMode = GL_CLAMP_TO_EDGE;
		}

		isMipmap = true;

		glBindTexture(type, id);
		glTexImage2D(type, 0, channelFormat, size.width, size.height, 0, pixelFormat, dataFormat, imgResult);
		if (isMipmap)
			glGenerateMipmap(type);
		//解除绑定
		glBindTexture(type, 0);
		// 释放资源
		stbi_image_free(imgResult);

		return true;
	}

	//bool LoadFromFile(string path) override
	//{

	//}
};