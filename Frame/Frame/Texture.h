// 纹理基类，纹理内容可以为空，也可以读取image，也可以作为颜色附件添加在帧缓冲
#pragma once
#include<string>
#include<glad/glad.h>
#include<iostream>
using namespace std;
#include"stb_image.h"

#include"PublicStruct.h"

class Texture
{
public:
	GLuint id;

	GLint channelFormat;
	GLenum pixelFormat;
	GLenum dataFormat;
	GLuint type;
	GLuint warpSMode;
	GLuint warpTMode;
	//GLuint warpRMode;
	GLuint minFilter;
	GLuint magFilter;

	bool isMipmap;
	int numChannels;

	//bool isSetting;			// 标志是否已经设置过了

public:
	Texture()
	{
		//isSetting = false;
		// 默认值
		//warpSMode = GL_REPEAT;
		//warpTMode = GL_REPEAT;
		//minFilter = GL_LINEAR;
		//magFilter = GL_LINEAR;
		//pixelFormat = GL_RGB;
		//channelFormat = GL_RGB;
		//dataFormat = GL_UNSIGNED_BYTE;
		//isMipmap = true;
	}

	// 从文件读取纹理内容
	virtual bool CreateFromImage(string path) = 0;

public:
	GLuint GetChannelFormat() { return channelFormat; }
	GLenum GetPixelFormat() { return pixelFormat; }
	GLenum GetDataFormat() { return dataFormat; }

};