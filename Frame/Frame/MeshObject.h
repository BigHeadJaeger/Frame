#pragma once
#include"Object.h"
#include"VertexData.h"
typedef OpenMesh::TriMesh_ArrayKernelT<> Mesh;

class MeshObject:public Object
{
private:
	Mesh mesh;
	VertexData vertexData;
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
	template<typename T>
	void InitBox(T&& width, T&& height, T&& depth);
	void InitSphere(float radius, int slice, int stack);
	void InitGrid(float width, float height, int m, int n);

	void InitBufferData()override;
	//void UpdateBufferData() override;
	void Update(float dt)override;
	void Draw()override;
};

template<typename T>
inline void MeshObject::InitBox(T&& width, T&& height, T&& depth)
{
	//providedTex = true;
	mesh.request_vertex_texcoords2D();
	float halfW = width * 0.5f;
	float halfH = height * 0.5f;
	float halfD = depth * 0.5f;

	//初始化4*6=24个顶点
	Mesh::VertexHandle vHandles[24];
	vHandles[0] = mesh.add_vertex(Mesh::Point(-halfW, -halfH, -halfD));
	mesh.set_texcoord2D(vHandles[0], OpenMesh::Vec2f(0.f, 1.f));
	vHandles[1] = mesh.add_vertex(Mesh::Point(-halfW, halfH, -halfD));
	mesh.set_texcoord2D(vHandles[1], OpenMesh::Vec2f(0.f, 0.f));
	vHandles[2] = mesh.add_vertex(Mesh::Point(halfW, halfH, -halfD));
	mesh.set_texcoord2D(vHandles[2], OpenMesh::Vec2f(1.f, 0.f));
	vHandles[3] = mesh.add_vertex(Mesh::Point(halfW, -halfH, -halfD));
	mesh.set_texcoord2D(vHandles[3], OpenMesh::Vec2f(1.f, 1.f));

	vHandles[4] = mesh.add_vertex(Mesh::Point(-halfW, -halfH, halfD));
	mesh.set_texcoord2D(vHandles[4], OpenMesh::Vec2f(0.f, 1.f));
	vHandles[5] = mesh.add_vertex(Mesh::Point(-halfW, halfH, halfD));
	mesh.set_texcoord2D(vHandles[5], OpenMesh::Vec2f(0.0, 0.0));
	vHandles[6] = mesh.add_vertex(Mesh::Point(-halfW, halfH, -halfD));
	mesh.set_texcoord2D(vHandles[6], OpenMesh::Vec2f(1.f, 0.f));
	vHandles[7] = mesh.add_vertex(Mesh::Point(-halfW, -halfH, -halfD));
	mesh.set_texcoord2D(vHandles[7], OpenMesh::Vec2f(1.f, 1.f));

	vHandles[8] = mesh.add_vertex(Mesh::Point(halfW, -halfH, halfD));
	mesh.set_texcoord2D(vHandles[8], OpenMesh::Vec2f(0.f, 1.f));
	vHandles[9] = mesh.add_vertex(Mesh::Point(halfW, halfH, halfD));
	mesh.set_texcoord2D(vHandles[9], OpenMesh::Vec2f(0.0, 0.0));
	vHandles[10] = mesh.add_vertex(Mesh::Point(-halfW, halfH, halfD));
	mesh.set_texcoord2D(vHandles[10], OpenMesh::Vec2f(1.f, 0.f));
	vHandles[11] = mesh.add_vertex(Mesh::Point(-halfW, -halfH, halfD));
	mesh.set_texcoord2D(vHandles[11], OpenMesh::Vec2f(1.f, 1.f));

	vHandles[12] = mesh.add_vertex(Mesh::Point(halfW, -halfH, -halfD));
	mesh.set_texcoord2D(vHandles[12], OpenMesh::Vec2f(0.f, 1.f));
	vHandles[13] = mesh.add_vertex(Mesh::Point(halfW, halfH, -halfD));
	mesh.set_texcoord2D(vHandles[13], OpenMesh::Vec2f(0.0, 0.0));
	vHandles[14] = mesh.add_vertex(Mesh::Point(halfW, halfH, halfD));
	mesh.set_texcoord2D(vHandles[14], OpenMesh::Vec2f(1.f, 0.f));
	vHandles[15] = mesh.add_vertex(Mesh::Point(halfW, -halfH, halfD));
	mesh.set_texcoord2D(vHandles[15], OpenMesh::Vec2f(1.f, 1.f));

	vHandles[16] = mesh.add_vertex(Mesh::Point(-halfW, halfH, -halfD));
	mesh.set_texcoord2D(vHandles[16], OpenMesh::Vec2f(0.f, 1.f));
	vHandles[17] = mesh.add_vertex(Mesh::Point(-halfW, halfH, halfD));
	mesh.set_texcoord2D(vHandles[17], OpenMesh::Vec2f(0.0, 0.0));
	vHandles[18] = mesh.add_vertex(Mesh::Point(halfW, halfH, halfD));
	mesh.set_texcoord2D(vHandles[18], OpenMesh::Vec2f(1.f, 0.f));
	vHandles[19] = mesh.add_vertex(Mesh::Point(halfW, halfH, -halfD));
	mesh.set_texcoord2D(vHandles[19], OpenMesh::Vec2f(1.f, 1.f));

	vHandles[20] = mesh.add_vertex(Mesh::Point(-halfW, -halfH, halfD));
	mesh.set_texcoord2D(vHandles[20], OpenMesh::Vec2f(0.f, 1.f));
	vHandles[21] = mesh.add_vertex(Mesh::Point(-halfW, -halfH, -halfD));
	mesh.set_texcoord2D(vHandles[21], OpenMesh::Vec2f(0.0, 0.0));
	vHandles[22] = mesh.add_vertex(Mesh::Point(halfW, -halfH, -halfD));
	mesh.set_texcoord2D(vHandles[22], OpenMesh::Vec2f(1.f, 0.f));
	vHandles[23] = mesh.add_vertex(Mesh::Point(halfW, -halfH, halfD));
	mesh.set_texcoord2D(vHandles[23], OpenMesh::Vec2f(1.f, 1.f));

	//初始化6个面（12个三角形）
	std::vector<Mesh::VertexHandle>  face_vhandles;
	//背面
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[0]);
	face_vhandles.push_back(vHandles[1]);
	face_vhandles.push_back(vHandles[2]);
	mesh.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[0]);
	face_vhandles.push_back(vHandles[2]);
	face_vhandles.push_back(vHandles[3]);
	mesh.add_face(face_vhandles);
	//左侧面
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[4]);
	face_vhandles.push_back(vHandles[5]);
	face_vhandles.push_back(vHandles[6]);
	mesh.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[4]);
	face_vhandles.push_back(vHandles[6]);
	face_vhandles.push_back(vHandles[7]);
	mesh.add_face(face_vhandles);
	//正面
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[8]);
	face_vhandles.push_back(vHandles[9]);
	face_vhandles.push_back(vHandles[10]);
	mesh.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[8]);
	face_vhandles.push_back(vHandles[10]);
	face_vhandles.push_back(vHandles[11]);
	mesh.add_face(face_vhandles);
	//右侧面
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[12]);
	face_vhandles.push_back(vHandles[13]);
	face_vhandles.push_back(vHandles[14]);
	mesh.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[12]);
	face_vhandles.push_back(vHandles[14]);
	face_vhandles.push_back(vHandles[15]);
	mesh.add_face(face_vhandles);
	//上面
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[16]);
	face_vhandles.push_back(vHandles[17]);
	face_vhandles.push_back(vHandles[18]);
	mesh.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[16]);
	face_vhandles.push_back(vHandles[18]);
	face_vhandles.push_back(vHandles[19]);
	mesh.add_face(face_vhandles);
	//下面
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[20]);
	face_vhandles.push_back(vHandles[21]);
	face_vhandles.push_back(vHandles[22]);
	mesh.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[20]);
	face_vhandles.push_back(vHandles[22]);
	face_vhandles.push_back(vHandles[23]);
	mesh.add_face(face_vhandles);

	//计算法向量
	mesh.request_vertex_normals();
	mesh.request_face_normals();
	mesh.update_normals();
	mesh.release_face_normals();
}

inline void MeshObject::InitGrid(float width, float height, int m, int n)
{
	mesh.request_vertex_texcoords2D();

	auto nVertsRow = m + 1;			//x方向顶点数
	auto nVertsCol = n + 1;			//z方向顶点数

	auto oX = -width * 0.5f;			//x方向的起始位置
	auto oZ = height * 0.5f;			//z方向的起始位置

	auto dX = width / m;			//变化率
	auto dZ = height / n;

	Mesh::VertexHandle* vHandles;
	vHandles = new Mesh::VertexHandle[nVertsCol * nVertsRow];
	//pointsData.resize(nVertsCol * nVertsRow);

	//从左上角开始逐行添加顶点信息
	for (int i = 0; i < nVertsCol; i++)
	{
		float tempZ = oZ - dZ * i;
		for (int j = 0; j < nVertsRow; j++)
		{
			int index = i * nVertsRow + j;
			//顶点
			vHandles[index] = mesh.add_vertex(Mesh::Point(oX + dX * j, 0.f, tempZ));
			//纹理
			mesh.set_texcoord2D(vHandles[index], OpenMesh::Vec2f(dX * j, dZ * i));
		}
	}

	//一共m*n个格子，一个格子分为两个三角形则有6个顶点
	int temp = 0;
	std::vector<Mesh::VertexHandle>  face_vhandles;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			face_vhandles.clear();
			face_vhandles.push_back(vHandles[i * nVertsRow + j]);
			face_vhandles.push_back(vHandles[i * nVertsRow + j + 1]);
			face_vhandles.push_back(vHandles[(i + 1) * nVertsRow + j]);
			mesh.add_face(face_vhandles);

			face_vhandles.clear();
			face_vhandles.push_back(vHandles[i * nVertsRow + j + 1]);
			face_vhandles.push_back(vHandles[(i + 1) * nVertsRow + j + 1]);
			face_vhandles.push_back(vHandles[(i + 1) * nVertsRow + j]);
			mesh.add_face(face_vhandles);
		}
	}

	delete[] vHandles;

	//计算法向量
	mesh.request_vertex_normals();
	mesh.request_face_normals();
	mesh.update_normals();
	mesh.release_face_normals();
}
