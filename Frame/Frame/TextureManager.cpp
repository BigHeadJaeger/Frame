#include "TextureManager.h"

shared_ptr<Texture> TextureManager::InitTexture(string path)
{
	shared_ptr<Texture> texture = make_shared<Texture>();
	texture->LoadTexture(path);
	textureMap.insert(make_pair(path, texture));
	return texture;
}

shared_ptr<Texture> TextureManager::GetTexture(string path)
{
	auto it = textureMap.find(path);
	if (it != textureMap.end())
		return it->second;
	else
	{
		// Éú³ÉÎÆÀí
		auto texture = InitTexture(path);
		if (!texture)
		{
			cout << "get texture failled" << endl;
			return nullptr;
		}
		return texture;
	}
}
