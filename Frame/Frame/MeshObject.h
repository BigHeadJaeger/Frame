#pragma once
#include"Object.h"
typedef OpenMesh::TriMesh_ArrayKernelT<> Mesh;


class MeshObject:public Object
{
private:
	Mesh mesh;
private:
	void GetVertexDataArray();
public:
	MeshObject()
	{

	}
	~MeshObject()
	{

	}

	void readObjFile(string fileName);
	void InitBox(float width, float height, float depth);
	void InitSphere(float radius, int slice, int stack);
	void InitGrid(float radius, int slice, int stack);

	void InitBufferData()override;
	void UpdateBufferData() override;
	void Update(float dt)override;
	void Draw()override;
};