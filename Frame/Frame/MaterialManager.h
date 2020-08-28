// 管理所有的材质 目前材质用名字区分 可复用
#pragma once
#include"Material.h"

class MaterialManager
{
public:
	map<string, shared_ptr<Material>> materialMap;
private:
	MaterialManager() {};
public:
	static MaterialManager& GetInstance()
	{
		static MaterialManager instance;
		return instance;
	}
	
	MaterialManager(MaterialManager&) = delete;

	// 创建一个新的材质
	template<typename TYPE>
	shared_ptr<TYPE> CreateMaterial(string name)
	{
		auto it = materialMap.find(name);
		if (it != materialMap.end())
		{
			cout << "the " + name + "material is exist" << endl;
			return dynamic_pointer_cast<TYPE>(it->second);
		}

		auto material = make_shared<TYPE>();
		material->name = name;
		materialMap.insert(make_pair(name, material));
		return material;
	}

	shared_ptr<Material> GetMaterial(string name);
};
