#pragma once
#include<string>
#include<glm.hpp>
#include<OpenMesh/Core/IO/MeshIO.hh>
#include<OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

#include<assimp/Importer.hpp>
#include<assimp/postprocess.h>
#include<assimp/scene.h>





using namespace std;
using namespace glm;

typedef OpenMesh::TriMesh_ArrayKernelT<> MeshStruct;

class Mesh
{
public:
	MeshStruct meshStruct;

public:
	void readObjFile(string fileName);
	void InitBox(float width, float height, float depth);
	void InitSphere(float radius, int slice, int stack);
	void InitGrid(float width, float height, int m, int n);

	// ¶ÁÈ¡Ä£ÐÍ
	void LoadModel(string path);

private:
	void ProcessModelNode(aiNode* rootNode, const aiScene* scene);
};
