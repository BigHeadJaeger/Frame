// ģ��
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

// ģ�͵Ĵ�����Ҫ������������������һ��object���зֱ����
class Model
{
public:
	// һ��ģ�͵�����������
	vector<Mesh> meshs;

	// ��ȡģ��
	void LoadModel(string path);
private:
	void ProcessModelNode(aiNode* rootNode, const aiScene* scene);
	Mesh ProcessModelMesh(aiMesh* mesh, const aiScene* scene);
};