#include "ModelManager.h"

shared_ptr<Model> ModelManager::InitModel(string path)
{
	shared_ptr<Model> model = make_shared<Model>();
	if (model->LoadModel(path))
	{
		models.insert(make_pair(path, model));
		return model;
	}
	else
	{
		cout << "load model failed" << endl;
		return nullptr;
	}
}

shared_ptr<Model> ModelManager::GetModel(string path)
{
	auto it = models.find(path);
	if (it != models.end())
		return it->second;
	else
	{
		// º”‘ÿmodel
		auto res = InitModel(path);
		if (!res)
		{
			cout << "get model failed" << endl;
			return nullptr;
		}
		return res;
	}
}
