// 模型
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<assimp/Importer.hpp>
#include<assimp/postprocess.h>
#include<assimp/scene.h>

#include"Mesh.h"

//struct MeshNode
//{
//	Mesh meshData;
//
//};

// 模型的创建需要将其所有子网格生成一个object进行分别管理
class Model
{
public:
	// 一个模型的所有子网格
	vector<Mesh> meshs;

	// 读取模型
	void LoadModel(string path);
private:
	void ProcessModelNode(aiNode* rootNode, const aiScene* scene);
	Mesh ProcessModelMesh(aiMesh* mesh, const aiScene* scene);
};