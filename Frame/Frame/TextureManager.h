// �������е����� ȫ�ֵĵ��� ͬһ����ɶ�θ���
#pragma once
#include<vector>
#include<map>
#include<memory>
#include<iostream>
#include"Texture.h"

class TextureManager
{
private:
	TextureManager(){}
public:
	map<string, shared_ptr<Texture>> textureMap;
public:
	static TextureManager& GetInstance()
	{
		static TextureManager instacne;
		return instacne;
	}

	TextureManager(TextureManager&) = delete;
	shared_ptr<Texture> InitTexture(string path);
	shared_ptr<Texture> GetTexture(string path);
};