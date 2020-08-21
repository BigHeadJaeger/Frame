#pragma once
#include"Component.h"
#include"VertexData.h"
#include"Mesh.h"

// 将mesh
class MeshReference: public Component
{
public:
	Mesh mesh;
	VertexData vertexData;
	GLint drawType;
	size_t drawUnitNumber;		// 绘制顶点的数量
	bool meshChange;			// 标志网格数据发生变化
private:
	// 将mesh结构体中的数据改为opengl中通用的数据存储方式
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
