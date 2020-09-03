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
	shared_ptr<Object> Create(string path);

private:
	// 按照模型的网格文件递归生成树形object
	void ProcessModelNode(shared_ptr<MeshNode> meshNode, shared_ptr<Object> obj);

};