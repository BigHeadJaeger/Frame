#include "MaterialManager.h"

shared_ptr<Material> MaterialManager::GetMaterial(string name)
{
	auto it = materialMap.find(name);
	if (it != materialMap.end())
		return it->second;

	cout << "the specify material not exist" << endl;
	return nullptr;
}
