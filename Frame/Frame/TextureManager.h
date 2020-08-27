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
	std::map<string, shared_ptr<Texture>> textureMap;
public:
	static TextureManager& GetInstance()
	{
		static TextureManager instacne;
		return instacne;
	}

	TextureManager(TextureManager&) = delete;

	shared_ptr<Texture> InitTexture(string path)
	{
		shared_ptr<Texture> texture = make_shared<Texture>();
		texture->LoadTextureFromFile(path);
		return texture;
	}

	shared_ptr<Texture> GetTexture(string path)
	{
		auto it = textureMap.find(path);
		if (it != textureMap.end())
			return it->second;
		else
		{
			// ��������
			auto texture = InitTexture(path);
			if(!texture)
			{
				cout << "get texture failled" << endl;
				return nullptr;
			}
			textureMap.insert(make_pair(path, texture));

			return texture;
		}
	}


};