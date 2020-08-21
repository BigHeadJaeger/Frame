#pragma once
#include"Component.h"
#include"VertexData.h"
#include"Mesh.h"

// ��mesh
class MeshReference: public Component
{
public:
	Mesh mesh;
	VertexData vertexData;
	GLint drawType;
	size_t drawUnitNumber;		// ���ƶ��������
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

	void CreateBox(int width, int height, int depth)
	{
		meshChange = true;
		mesh.InitBox(width, height, depth);
		ConvertMeshData();
	}

	void CreateSphere(float radius, int slice = 20, int stack = 20)
	{
		meshChange = true;
		mesh.InitSphere(radius, slice, stack);
		ConvertMeshData();
	}

	void CreateGrid(float width, float height, int m = 10, int n = 10)
	{
		meshChange = true;
		mesh.InitGrid(width, height, m, n);
		ConvertMeshData();
	}
};
