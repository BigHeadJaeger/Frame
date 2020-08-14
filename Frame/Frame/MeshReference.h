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
	size_t drawUnitNumber;		// 绘制顶点的数量
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

	void CreateBox(int width, int height, int depth)
	{
		mesh.InitBox(width, height, depth);
		ConvertMeshData();
	}

	//void InitBufferData()override;
	//void UpdateBufferData() override;
};
