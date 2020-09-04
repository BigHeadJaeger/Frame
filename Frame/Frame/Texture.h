// 纹理类
#pragma once
#include<string>
#include<glad/glad.h>
#include<SOIL.h>
#include<iostream>
using namespace std;

//enum class TEXTURE_TYPE
//{
//	BASECOLOR,
//	NORMAL,
//	ROUGHNESS,
//	AO,
//	HEIGHT,
//	METALLIC
//};

class Texture
{
public:
	GLuint id;
	string filePath;

	unsigned char* imgResult;
	GLenum channelFormat;
	GLuint type;
	GLuint warpSMode;
	GLuint warpTMode;
	GLuint warpRMode;
	GLuint minFilter;
	GLuint magFilter;

	bool isMipmap;
	int width, height, numChannels;

	bool isSetting;			// 标志是否已经设置过了

public:
	Texture()
	{
		isSetting = false;
		//DefaultTex2DSetting();
	}

	// 将纹理设置为默认的2d参数
	void DefaultTex2DSetting()
	{
		if (!imgResult)
		{
			cout << "need load texture before setting" << endl;
			return;
		}
		type = GL_TEXTURE_2D;
		warpSMode = GL_REPEAT;
		warpTMode = GL_REPEAT;
		warpRMode = GL_REPEAT;
		minFilter = GL_LINEAR;
		magFilter = GL_LINEAR;

		if (numChannels == 1)
			channelFormat = GL_RED;
		else if (numChannels == 3)
			channelFormat = GL_RGB;
		else if (numChannels == 4)
		{
			channelFormat = GL_RGBA;
			warpSMode = GL_CLAMP_TO_EDGE;
			warpTMode = GL_CLAMP_TO_EDGE;
		}

		isMipmap = true;
	}
	// 只读取图片内容并保存，不进行设置
	void LoadTexture(string path);

	// 设置图片的属性，纹理的设置推迟到绑定材质之前，可按照需求先设置不同的属性(提高利用率和灵活性)
	void SettingTexture(bool isReset = false)
	{
		// 已经设置过了判断是否重置，否则不管是否重置都要设置一遍
		if (isSetting && !isReset)
			return;
		glBindTexture(type, id);
		//指定贴图方法
		glTexParameteri(type, GL_TEXTURE_WRAP_S, warpSMode);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, warpTMode);
		if (type == GL_TEXTURE_CUBE_MAP)
			glTexParameteri(type, GL_TEXTURE_WRAP_R, warpRMode);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);

		glTexImage2D(type, 0, channelFormat, width, height, 0, channelFormat, GL_UNSIGNED_BYTE, imgResult);
		if(isMipmap)
			glGenerateMipmap(type);
		//解除绑定并释放
		glBindTexture(type, 0);
		isSetting = true;
	}


	~Texture()
	{
		delete imgResult;
	}
};