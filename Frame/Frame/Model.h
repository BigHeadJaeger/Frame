// ģ��
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<assimp/Importer.hpp>
#include<assimp/postprocess.h>
#include<assimp/scene.h>

#include"Mesh.h"

// �����νṹ����model�µ�����������
class MeshNode
{
public:
	// һ���ڵ��¿����ж������
	vector<shared_ptr<Mesh>> data;
	// ���ӽڵ��б�
	std::list<shared_ptr<MeshNode>> children;
	// ���ڵ�ָ��
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

// ģ�͵Ĵ�����Ҫ������������������һ��object���зֱ����
class Model
{
public:
	// һ��ģ�͵�����������
	//vector<Mesh> meshs;

	shared_ptr<MeshNode> root;

	Model()
	{
		root = make_shared<MeshNode>();
	}


	// ��ȡģ��
	void LoadModel(string path);
private:
	void ProcessModelNode(aiNode* rootNode, const aiScene* scene, shared_ptr<MeshNode> parent);
	shared_ptr<Mesh> ProcessModelMesh(aiMesh* mesh, const aiScene* scene);
};