#pragma once
#include"Texture.h"


class Texture2D : public Texture
{
private:
	
public:
	Texture2D()
	{
		type = GL_TEXTURE_2D;

		// ��������
		glGenTextures(1, &id);
		glBindTexture(type, id);
		glTexParameteri(type, GL_TEXTURE_WRAP_S, warpSMode);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, warpTMode);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);
		glBindTexture(type, 0);
	}

	// ͨ���ߴ紴��������
	void Create(size_t _width, size_t _height, GLuint _channelFormat = GL_RGB, GLenum _pixelFormat = GL_RGB, bool _isMipMap = true)
	{
		width = _width;
		height = _height;
		channelFormat = _channelFormat;
		pixelFormat = _pixelFormat;
		isMipmap = _isMipMap;
		glBindTexture(type, id);
		glTexImage2D(type, 0, channelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, nullptr);
		if (isMipmap)
			glGenerateMipmap(type);
		
		glBindTexture(type, 0);
	}

	bool CreateFromFile(string path) override
	{
		unsigned char* imgResult;
		glGenTextures(1, &id);					//����һ������ID
		imgResult = stbi_load(path.c_str(), &width, &height, &numChannels, 0);

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
		glTexImage2D(type, 0, channelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, imgResult);
		if (isMipmap)
			glGenerateMipmap(type);
		//�����
		glBindTexture(type, 0);
		// �ͷ���Դ
		stbi_image_free(imgResult);

		return true;
	}

	//bool LoadFromFile(string path) override
	//{

	//}
};