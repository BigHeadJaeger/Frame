#pragma once
#include"Component.h"
#include"VertexData.h"
#include"Mesh.h"

// ��mesh
class MeshReference: public Component
{
public:
	shared_ptr<Mesh> mesh;
	//Mesh mesh;
	VertexData vertexData;
	bool meshChange;			// ��־�������ݷ����仯
private:
	// ��mesh�ṹ���е����ݸ�Ϊopengl��ͨ�õ����ݴ洢��ʽ
	void ConvertMeshData();

public:
	MeshReference()
	{

	}
	~MeshReference()
	{

	}

	void Update(float dt)
	{
		if (!isActive)
			return;
	}

	void CreateBox(float width, float height, float depth)
	{
		mesh = make_shared<Mesh>();
		meshChange = true;
		mesh->InitBox(width, height, depth);
		ConvertMeshData();
	}

	void CreateSphere(float radius, int slice = 20, int stack = 20)
	{
		mesh = make_shared<Mesh>();
		meshChange = true;
		mesh->InitSphere(radius, slice, stack);
		ConvertMeshData();
	}

	void CreateGrid(float width, float height, int m = 10, int n = 10)
	{
		mesh = make_shared<Mesh>();
		meshChange = true;
		mesh->InitGrid(width, height, m, n);
		ConvertMeshData();
	}

	void SetMesh(shared_ptr<Mesh> _mesh)
	{
		meshChange = true;
		mesh = _mesh;
		ConvertMeshData();
	}
};
