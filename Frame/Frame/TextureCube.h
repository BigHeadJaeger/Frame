#pragma once
#include"Texture.h"

class TextureCube : public Texture
{
private:
	
public:
	GLuint warpRMode;

public:
	TextureCube()
	{
		warpRMode = GL_REPEAT;
	}

	// ��ȡһ��image�ֱ���Ϊcube��6����
	//bool LoadFromFile(string path) override
	//{

	//}

	// ��ȡĳһ�ļ����µ�����ͼƬ��Ϊ������
	bool LoadImages(string prefix, string name)
	{

	}

	// �ֱ��ȡ������
	void LoadPostiveX(string path);
	void LoadNegativeX(string path);
	void LoadPostiveY(string path);
	void LoadNegativeY(string path);
	void LoadPostiveZ(string path);
	void LoadNegativeZ(string path);
};