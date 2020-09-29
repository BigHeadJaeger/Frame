// �������е����� ȫ�ֵĵ��� ͬһ����ɶ�θ���
#pragma once
#include<vector>
#include<map>
#include<memory>
#include<iostream>
#include"Texture2D.h"

class TextureManager
{
private:
	TextureManager(){}
public:
	map<string, shared_ptr<Texture2D>> textureMap;
public:
	static TextureManager& GetInstance()
	{
		static TextureManager instacne;
		return instacne;
	}
	TextureManager(TextureManager&) = delete;

	shared_ptr<Texture2D> InitTexture2D(string path);
	shared_ptr<Texture2D> GetTexture2D(string path);
};