// �������еĲ��� Ŀǰ�������������� �ɸ���
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

	// ����һ���µĲ���
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
