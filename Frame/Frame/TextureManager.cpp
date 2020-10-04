#include "TextureManager.h"

shared_ptr<Texture2D> TextureManager::InitTexture2D(string path)
{
	shared_ptr<Texture2D> texture = make_shared<Texture2D>();
	texture->CreateFromImage(path);
	textureMap.insert(make_pair(path, texture));
	return texture;
}

shared_ptr<Texture2D> TextureManager::GetTexture2D(string path)
{
	auto it = textureMap.find(path);
	if (it != textureMap.end())
		return it->second;
	else
	{
		// Éú³ÉÎÆÀí
		auto texture = InitTexture2D(path);
		if (!texture)
		{
			cout << "get texture failled" << endl;
			return nullptr;
		}
		return texture;
	}
}
