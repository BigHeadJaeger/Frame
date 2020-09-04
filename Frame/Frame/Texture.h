// ������
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

	bool isSetting;			// ��־�Ƿ��Ѿ����ù���

public:
	Texture()
	{
		isSetting = false;
		//DefaultTex2DSetting();
	}

	// ����������ΪĬ�ϵ�2d����
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
	// ֻ��ȡͼƬ���ݲ����棬����������
	void LoadTexture(string path);

	// ����ͼƬ�����ԣ�����������Ƴٵ��󶨲���֮ǰ���ɰ������������ò�ͬ������(��������ʺ������)
	void SettingTexture(bool isReset = false)
	{
		// �Ѿ����ù����ж��Ƿ����ã����򲻹��Ƿ����ö�Ҫ����һ��
		if (isSetting && !isReset)
			return;
		glBindTexture(type, id);
		//ָ����ͼ����
		glTexParameteri(type, GL_TEXTURE_WRAP_S, warpSMode);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, warpTMode);
		if (type == GL_TEXTURE_CUBE_MAP)
			glTexParameteri(type, GL_TEXTURE_WRAP_R, warpRMode);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);

		glTexImage2D(type, 0, channelFormat, width, height, 0, channelFormat, GL_UNSIGNED_BYTE, imgResult);
		if(isMipmap)
			glGenerateMipmap(type);
		//����󶨲��ͷ�
		glBindTexture(type, 0);
		isSetting = true;
	}


	~Texture()
	{
		delete imgResult;
	}
};