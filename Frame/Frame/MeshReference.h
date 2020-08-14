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
	size_t drawUnitNumber;		// ���ƶ��������
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

	void CreateBox(int width, int height, int depth)
	{
		mesh.InitBox(width, height, depth);
		ConvertMeshData();
	}

	//void InitBufferData()override;
	//void UpdateBufferData() override;
};
