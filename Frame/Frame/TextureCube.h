// 图片可以是直接读取文件的，使用已有的texture的
#pragma once
#include"Texture.h"

// texture cube 的长宽必须相等
class TextureCube : public Texture
{
private:
	GLuint warpRMode;
	Size2D size;

private:
	bool LoadTexByDir(GLenum dir, string path)
	{
		glBindTexture(type, id);
		int width, height, numChannels;
		unsigned char* pResult;
		pResult = stbi_load(path.c_str(), &width, &height, &numChannels, 0);

		if (pResult)
		{
			glTexImage2D(dir, 0, channelFormat, width, height, 0, pixelFormat, dataFormat, pResult);
			stbi_image_free(pResult);
		}
		else
		{
			cout << "the " + path + " image load failed" << endl;
			stbi_image_free(pResult);
			return false;
		}

		glBindTexture(type, 0);
		return true;
	}
public:
	TextureCube(int length = 128)
	{
		size.width = length;
		size.height = length;

		type = GL_TEXTURE_CUBE_MAP;

		warpRMode = GL_CLAMP_TO_EDGE;
		warpSMode = GL_CLAMP_TO_EDGE;
		warpTMode = GL_CLAMP_TO_EDGE;
		minFilter = GL_LINEAR;
		magFilter = GL_LINEAR;

		pixelFormat = GL_RGB;
		channelFormat = GL_RGB;
		dataFormat = GL_UNSIGNED_BYTE;

		glGenTextures(1, &id);
		glBindTexture(type, id);
		glTexParameteri(type, GL_TEXTURE_WRAP_S, warpSMode);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, warpTMode);
		glTexParameteri(type, GL_TEXTURE_WRAP_R, warpRMode);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);
		for (int i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, channelFormat, length, length, 0, pixelFormat, dataFormat, nullptr);
		}
		glBindTexture(type, 0);
	}

	//// 通过尺寸创建空纹理
	//void Create(size_t _length, GLuint _channelFormat = GL_RGB, GLenum _pixelFormat = GL_RGB, GLenum _dataFormat = GL_UNSIGNED_BYTE, bool _isMipMap = true)
	//{
	//	length = _length;
	//	channelFormat = _channelFormat;
	//	pixelFormat = _pixelFormat;
	//	isMipmap = _isMipMap;
	//	glBindTexture(type, id);
	//	for (int i = 0; i < 6; i++)
	//	{
	//		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, channelFormat, length, length, 0, pixelFormat, dataFormat, nullptr);
	//	}
	//	//glTexImage2D(type, 0, channelFormat, width, height, 0, pixelFormat, dataFormat, nullptr);
	//	//if (isMipmap)
	//	//	glGenerateMipmap(type);

	//	glBindTexture(type, 0);
	//}

	// 读取一张image分别作为cube的6个面
	bool CreateFromImage(string path) override
	{
		glBindTexture(type, id);
		int width, height, numChannels;
		unsigned char* pResult;
		pResult = stbi_load(path.c_str(), &width, &height, &numChannels, 0);

		if (pResult)
		{
			for (int i = 0; i < 6; i++)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, channelFormat, width, height, 0, pixelFormat, dataFormat, pResult);
			}
			stbi_image_free(pResult);
		}
		else
		{
			cout << "the " + path + " image load failed" << endl;
			stbi_image_free(pResult);
			return false;
		}

		glBindTexture(type, 0);
		return true;
	}
	

	//// 读取某一文件夹下的六张图片作为六个面
	//bool LoadImages(string prefix, string name)
	//{

	//}

	// 分别读取六个面（从原始图片）
	bool LoadPostiveX(string path)
	{
		return LoadTexByDir(GL_TEXTURE_CUBE_MAP_POSITIVE_X, path);
	}
	bool LoadNegativeX(string path)
	{
		return LoadTexByDir(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, path);
	}
	bool LoadPostiveY(string path)
	{
		return LoadTexByDir(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, path);

	}
	bool LoadNegativeY(string path)
	{
		return LoadTexByDir(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, path);

	}
	bool LoadPostiveZ(string path)
	{
		return LoadTexByDir(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, path);

	}
	bool LoadNegativeZ(string path)
	{
		return LoadTexByDir(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, path);

	}

	// 形成六个面（从已有的Texture2D中，可以在从texture上封装一层）

};