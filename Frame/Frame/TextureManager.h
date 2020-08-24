// 管理所有的纹理 全局的单利 防止同一纹理多次初始化
#pragma once
#include<vector>
#include<map>
#include"Texture.h"

class TextureManager
{
public:
	std::map<string, Texture> textureMap;

};