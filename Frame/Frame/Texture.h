// Œ∆¿Ì¿‡
#pragma once
#include<string>
#include<glad/glad.h>
#include<SOIL.h>
using namespace std;

enum class TEXTURE_TYPE
{
	BASECOLOR,
	NORMAL,
	ROUGHNESS,
	AO,
	HEIGHT,
	METALLIC
};

class Texture
{
public:
	GLuint id;
	string filePath;
	//string type;
public:
	//void InitTexture(string _type, string _path)
	//{
	//	type = _type;
	//	LoadTextureFromFile(_path);
	//}
	void LoadTextureFromFile(string path);
};