#pragma once
#include<string>
#include<glm.hpp>
#include<OpenMesh/Core/IO/MeshIO.hh>
#include<OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
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
};
