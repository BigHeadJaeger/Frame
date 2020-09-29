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

	// 读取一张image分别作为cube的6个面
	//bool LoadFromFile(string path) override
	//{

	//}

	// 读取某一文件夹下的六张图片作为六个面
	bool LoadImages(string prefix, string name)
	{

	}

	// 分别读取六个面
	void LoadPostiveX(string path);
	void LoadNegativeX(string path);
	void LoadPostiveY(string path);
	void LoadNegativeY(string path);
	void LoadPostiveZ(string path);
	void LoadNegativeZ(string path);
};