// Œ∆¿Ì¿‡
#pragma once
#include<string>
#include<glad/glad.h>
using namespace std;

class Texture
{
public:
	GLuint id;
	string type;
	string path;
public:

	void InitTexture(string _type, string _path)
	{
		type = _type;
		LoadTextureFromFile(_path);
	}
	void LoadTextureFromFile(string path);
};