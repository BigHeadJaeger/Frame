// 纹理基类，纹理内容可以为空，也可以读取image，也可以作为颜色附件添加在帧缓冲
#pragma once
#include<string>
#include<glad/glad.h>
#include<iostream>
using namespace std;

#include"stb_image.h"

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

	GLint channelFormat;
	GLenum pixelFormat;
	GLuint type;
	GLuint warpSMode;
	GLuint warpTMode;
	//GLuint warpRMode;
	GLuint minFilter;
	GLuint magFilter;

	bool isMipmap;
	int width, height, numChannels;

	//bool isSetting;			// 标志是否已经设置过了

public:
	Texture()
	{
		//isSetting = false;
		// 默认值
		warpSMode = GL_REPEAT;
		warpTMode = GL_REPEAT;
		minFilter = GL_LINEAR;
		magFilter = GL_LINEAR;
		pixelFormat = GL_RGB;
		channelFormat = GL_RGB;
		isMipmap = true;
	}

	//// 创建一个没有内容的纹理
	//virtual void Create() = 0;

	// 从文件读取纹理内容
	virtual bool CreateFromFile(string path) = 0;

	//// 设置图片的属性，纹理的设置推迟到绑定材质之前，可按照需求先设置不同的属性(提高利用率和灵活性)
	//void SettingTexture(bool isReset = false)
	//{
	//	// 已经设置过了判断是否重置，否则不管是否重置都要设置一遍
	//	if (isSetting && !isReset)
	//		return;
	//	glBindTexture(type, id);
	//	//指定贴图方法
	//	glTexParameteri(type, GL_TEXTURE_WRAP_S, warpSMode);
	//	glTexParameteri(type, GL_TEXTURE_WRAP_T, warpTMode);
	//	//if (type == GL_TEXTURE_CUBE_MAP)
	//	//	glTexParameteri(type, GL_TEXTURE_WRAP_R, warpRMode);
	//	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
	//	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);

	//	glTexImage2D(type, 0, channelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, imgResult);
	//	if(isMipmap)
	//		glGenerateMipmap(type);
	//	//解除绑定并释放
	//	glBindTexture(type, 0);
	//	isSetting = true;
	//}


	void LoadHDRTexture(string path);

	//~Texture()
	//{
	//	delete imgResult;
	//}
};