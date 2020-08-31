// ������ģ���е�ÿ������������Object�����ӵ�������
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

	// ģ�ͽ���
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
	// ����ģ�͵������ļ��ݹ���������object
	void ProcessModelNode(shared_ptr<MeshNode> meshNode, shared_ptr<Object> obj)
	{
		obj->AddComponent<Transform>();
		if (meshNode->data)
		{
			obj->SetName(meshNode->data->name);
			auto reference = obj->AddComponent<MeshReference>();
			reference->SetMesh(meshNode->data);
			auto meshRender = obj->AddComponent<MeshRenderer>();
			// ����������Դ��Ĳ�����ֱ��ʹ��
			if (!meshNode->data->material.expired())
				meshRender->material = meshNode->data->material.lock();
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