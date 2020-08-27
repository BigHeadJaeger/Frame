// 用来将模型中的每个子网格生成Object并添加到场景中
#pragma once
#include"ModelManager.h"
#include"ObjectManager.h"
#include"RenderFrameModel.h"

class ModelGenerator
{
private:
	ModelGenerator() {}
public:
	static ModelGenerator& GetInstance()
	{
		static ModelGenerator instance;
		return instance;
	}

	ModelGenerator(ModelGenerator&) = delete;

	// 模型建造
	shared_ptr<Object> Create(string path)
	{
		decltype(auto) modelManager = ModelManager::GetInstance();
		decltype(auto) objectManager = RenderFrameModel::GetInstance().GetCurrentObjectManager();

		auto model = modelManager.GetModel(path);
		if (!model)
		{
			cout << "create model failed" << endl;
			return nullptr;
		}
		//model->root->data.
		shared_ptr<Object> rootObj = make_shared<Object>();
		ProcessModelNode(model->root, rootObj);

		return rootObj;
	}

private:
	void ProcessModelNode(shared_ptr<MeshNode> meshNode, shared_ptr<Object> obj)
	{
		obj->AddComponent<Transform>();
		if (meshNode->data)
		{
			obj->SetName(meshNode->data->name);
			auto reference = obj->AddComponent<MeshReference>();
			reference->SetMesh(meshNode->data);
			obj->AddComponent<MeshRenderer>();
		}
		else
			obj->SetName("Model");

		for (auto it = meshNode->children.begin(); it != meshNode->children.end(); it++)
		{
			shared_ptr<Object> child = make_shared<Object>();
			obj->AddChild(child);
			ProcessModelNode((*it), child);
		}
	}

};