// ������ģ���е�ÿ������������Object����ӵ�������
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
	shared_ptr<Object> Create(string path);

private:
	// ����ģ�͵������ļ��ݹ���������object
	void ProcessModelNode(shared_ptr<MeshNode> meshNode, shared_ptr<Object> obj);

};