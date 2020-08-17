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

	}

	void CreateBox(int width, int height, int depth)
	{
		meshChange = true;
		mesh.InitBox(width, height, depth);
		ConvertMeshData();
	}

	//void InitBufferData()override;
	//void UpdateBufferData() override;
};
