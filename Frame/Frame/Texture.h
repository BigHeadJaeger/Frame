// ������࣬�������ݿ���Ϊ�գ�Ҳ���Զ�ȡimage��Ҳ������Ϊ��ɫ���������֡����
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

	//bool isSetting;			// ��־�Ƿ��Ѿ����ù���

public:
	Texture()
	{
		//isSetting = false;
		// Ĭ��ֵ
		//warpSMode = GL_REPEAT;
		//warpTMode = GL_REPEAT;
		//minFilter = GL_LINEAR;
		//magFilter = GL_LINEAR;
		//pixelFormat = GL_RGB;
		//channelFormat = GL_RGB;
		//dataFormat = GL_UNSIGNED_BYTE;
		//isMipmap = true;
	}

	// ���ļ���ȡ��������
	virtual bool CreateFromImage(string path) = 0;

public:
	GLuint GetChannelFormat() { return channelFormat; }
	GLenum GetPixelFormat() { return pixelFormat; }
	GLenum GetDataFormat() { return dataFormat; }

};