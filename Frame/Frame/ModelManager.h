// �����������е�ģ�ͣ����ع�һ�εĿ��Ը���, ����
#pragma once
#include<map>
#include<iostream>
#include"Model.h"

class ModelManager
{
private:
	ModelManager() {};
public:
	map<string, shared_ptr<Model>> models;
	static ModelManager& GetInstance()
	{
		static ModelManager instance;
		return instance;
	}

	ModelManager(ModelManager&) = delete;

	shared_ptr<Model> InitModel(string path);
	shared_ptr<Model> GetModel(string path);
};