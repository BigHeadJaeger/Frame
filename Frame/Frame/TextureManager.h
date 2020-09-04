// 管理所有的纹理 全局的单利 同一纹理可多次复用
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