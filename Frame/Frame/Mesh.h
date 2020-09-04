#pragma once
#include<string>
#include<glm.hpp>
#include<OpenMesh/Core/IO/MeshIO.hh>
#include<OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
using namespace std;
using namespace glm;

#include"Material.h"

typedef OpenMesh::TriMesh_ArrayKernelT<> MeshStruct;

class Mesh
{
public:
	MeshStruct meshStruct;
	string name;

	weak_ptr<Material> material;
public:
	void readObjFile(string fileName);
	void InitBox(float width, float height, float depth);
	void InitSphere(float radius, int slice, int stack);
	void InitGrid(float width, float height, int m, int n);

	// ¶ÁÈ¡Ä£ÐÍ
	//void LoadModel(string path);
	MeshStruct& GetMeshStruct()
	{
		return meshStruct;
	}

private:
	//void ProcessModelNode(aiNode* rootNode, const aiScene* scene);
	//void ProcessModelMesh(aiMesh* mesh, const aiScene* scene);
};
