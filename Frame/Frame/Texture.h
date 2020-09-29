// ������࣬�������ݿ���Ϊ�գ�Ҳ���Զ�ȡimage��Ҳ������Ϊ��ɫ���������֡����
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

	//bool isSetting;			// ��־�Ƿ��Ѿ����ù���

public:
	Texture()
	{
		//isSetting = false;
		// Ĭ��ֵ
		warpSMode = GL_REPEAT;
		warpTMode = GL_REPEAT;
		minFilter = GL_LINEAR;
		magFilter = GL_LINEAR;
		pixelFormat = GL_RGB;
		channelFormat = GL_RGB;
		isMipmap = true;
	}

	//// ����һ��û�����ݵ�����
	//virtual void Create() = 0;

	// ���ļ���ȡ��������
	virtual bool CreateFromFile(string path) = 0;

	//// ����ͼƬ�����ԣ�����������Ƴٵ��󶨲���֮ǰ���ɰ������������ò�ͬ������(��������ʺ������)
	//void SettingTexture(bool isReset = false)
	//{
	//	// �Ѿ����ù����ж��Ƿ����ã����򲻹��Ƿ����ö�Ҫ����һ��
	//	if (isSetting && !isReset)
	//		return;
	//	glBindTexture(type, id);
	//	//ָ����ͼ����
	//	glTexParameteri(type, GL_TEXTURE_WRAP_S, warpSMode);
	//	glTexParameteri(type, GL_TEXTURE_WRAP_T, warpTMode);
	//	//if (type == GL_TEXTURE_CUBE_MAP)
	//	//	glTexParameteri(type, GL_TEXTURE_WRAP_R, warpRMode);
	//	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
	//	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);

	//	glTexImage2D(type, 0, channelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, imgResult);
	//	if(isMipmap)
	//		glGenerateMipmap(type);
	//	//����󶨲��ͷ�
	//	glBindTexture(type, 0);
	//	isSetting = true;
	//}


	void LoadHDRTexture(string path);

	//~Texture()
	//{
	//	delete imgResult;
	//}
};