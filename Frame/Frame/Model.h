// 模型
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<assimp/Importer.hpp>
#include<assimp/postprocess.h>
#include<assimp/scene.h>

#include"Mesh.h"

// 用树形结构保存model下的所有子网格
class MeshNode
{
public:
	// 一个节点下可能有多个网格
	vector<shared_ptr<Mesh>> data;
	// 孩子节点列表
	std::list<shared_ptr<MeshNode>> children;
	// 父节点指针
	shared_ptr<MeshNode> parent;

public:
	void AddChild(shared_ptr<MeshNode> data)
	{

	}
};

//class MeshTree
//{
//public:
//	shared_ptr<MeshNode> root;
//
//};

// 模型的创建需要将其所有子网格生成一个object进行分别管理
class Model
{
public:
	// 一个模型的所有子网格
	//vector<Mesh> meshs;

	shared_ptr<MeshNode> root;

	Model()
	{
		root = make_shared<MeshNode>();
	}


	// 读取模型
	void LoadModel(string path);
private:
	void ProcessModelNode(aiNode* rootNode, const aiScene* scene, shared_ptr<MeshNode> parent);
	shared_ptr<Mesh> ProcessModelMesh(aiMesh* mesh, const aiScene* scene);
};