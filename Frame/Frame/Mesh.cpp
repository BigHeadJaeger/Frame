#include"Mesh.h"
#include"Const.h"

void Mesh::readObjFile(string fileName)
{
	meshStruct.request_vertex_normals();

	OpenMesh::IO::Options opt;
	if (!OpenMesh::IO::read_mesh(meshStruct, fileName), opt)
	{
		cout << "init mesh failed" << endl;
	}

	if (!opt.check(OpenMesh::IO::Options::VertexNormal))
	{
		meshStruct.request_face_normals();
		meshStruct.update_normals();
		meshStruct.release_face_normals();
	}

	meshStruct.request_vertex_texcoords2D();
}

void Mesh::InitBox(float width, float height, float depth)
{
	meshStruct.clean();
	//providedTex = true;
	meshStruct.request_vertex_texcoords2D();
	float halfW = width * 0.5f;
	float halfH = height * 0.5f;
	float halfD = depth * 0.5f;

	//��ʼ��4*6=24������
	MeshStruct::VertexHandle vHandles[24];
	vHandles[0] = meshStruct.add_vertex(MeshStruct::Point(-halfW, -halfH, -halfD));
	meshStruct.set_texcoord2D(vHandles[0], OpenMesh::Vec2f(0.f, 1.f));
	vHandles[1] = meshStruct.add_vertex(MeshStruct::Point(-halfW, halfH, -halfD));
	meshStruct.set_texcoord2D(vHandles[1], OpenMesh::Vec2f(0.f, 0.f));
	vHandles[2] = meshStruct.add_vertex(MeshStruct::Point(halfW, halfH, -halfD));
	meshStruct.set_texcoord2D(vHandles[2], OpenMesh::Vec2f(1.f, 0.f));
	vHandles[3] = meshStruct.add_vertex(MeshStruct::Point(halfW, -halfH, -halfD));
	meshStruct.set_texcoord2D(vHandles[3], OpenMesh::Vec2f(1.f, 1.f));

	vHandles[4] = meshStruct.add_vertex(MeshStruct::Point(-halfW, -halfH, halfD));
	meshStruct.set_texcoord2D(vHandles[4], OpenMesh::Vec2f(0.f, 1.f));
	vHandles[5] = meshStruct.add_vertex(MeshStruct::Point(-halfW, halfH, halfD));
	meshStruct.set_texcoord2D(vHandles[5], OpenMesh::Vec2f(0.0, 0.0));
	vHandles[6] = meshStruct.add_vertex(MeshStruct::Point(-halfW, halfH, -halfD));
	meshStruct.set_texcoord2D(vHandles[6], OpenMesh::Vec2f(1.f, 0.f));
	vHandles[7] = meshStruct.add_vertex(MeshStruct::Point(-halfW, -halfH, -halfD));
	meshStruct.set_texcoord2D(vHandles[7], OpenMesh::Vec2f(1.f, 1.f));

	vHandles[8] = meshStruct.add_vertex(MeshStruct::Point(halfW, -halfH, halfD));
	meshStruct.set_texcoord2D(vHandles[8], OpenMesh::Vec2f(0.f, 1.f));
	vHandles[9] = meshStruct.add_vertex(MeshStruct::Point(halfW, halfH, halfD));
	meshStruct.set_texcoord2D(vHandles[9], OpenMesh::Vec2f(0.0, 0.0));
	vHandles[10] = meshStruct.add_vertex(MeshStruct::Point(-halfW, halfH, halfD));
	meshStruct.set_texcoord2D(vHandles[10], OpenMesh::Vec2f(1.f, 0.f));
	vHandles[11] = meshStruct.add_vertex(MeshStruct::Point(-halfW, -halfH, halfD));
	meshStruct.set_texcoord2D(vHandles[11], OpenMesh::Vec2f(1.f, 1.f));

	vHandles[12] = meshStruct.add_vertex(MeshStruct::Point(halfW, -halfH, -halfD));
	meshStruct.set_texcoord2D(vHandles[12], OpenMesh::Vec2f(0.f, 1.f));
	vHandles[13] = meshStruct.add_vertex(MeshStruct::Point(halfW, halfH, -halfD));
	meshStruct.set_texcoord2D(vHandles[13], OpenMesh::Vec2f(0.0, 0.0));
	vHandles[14] = meshStruct.add_vertex(MeshStruct::Point(halfW, halfH, halfD));
	meshStruct.set_texcoord2D(vHandles[14], OpenMesh::Vec2f(1.f, 0.f));
	vHandles[15] = meshStruct.add_vertex(MeshStruct::Point(halfW, -halfH, halfD));
	meshStruct.set_texcoord2D(vHandles[15], OpenMesh::Vec2f(1.f, 1.f));

	vHandles[16] = meshStruct.add_vertex(MeshStruct::Point(-halfW, halfH, -halfD));
	meshStruct.set_texcoord2D(vHandles[16], OpenMesh::Vec2f(0.f, 1.f));
	vHandles[17] = meshStruct.add_vertex(MeshStruct::Point(-halfW, halfH, halfD));
	meshStruct.set_texcoord2D(vHandles[17], OpenMesh::Vec2f(0.0, 0.0));
	vHandles[18] = meshStruct.add_vertex(MeshStruct::Point(halfW, halfH, halfD));
	meshStruct.set_texcoord2D(vHandles[18], OpenMesh::Vec2f(1.f, 0.f));
	vHandles[19] = meshStruct.add_vertex(MeshStruct::Point(halfW, halfH, -halfD));
	meshStruct.set_texcoord2D(vHandles[19], OpenMesh::Vec2f(1.f, 1.f));

	vHandles[20] = meshStruct.add_vertex(MeshStruct::Point(-halfW, -halfH, halfD));
	meshStruct.set_texcoord2D(vHandles[20], OpenMesh::Vec2f(0.f, 1.f));
	vHandles[21] = meshStruct.add_vertex(MeshStruct::Point(-halfW, -halfH, -halfD));
	meshStruct.set_texcoord2D(vHandles[21], OpenMesh::Vec2f(0.0, 0.0));
	vHandles[22] = meshStruct.add_vertex(MeshStruct::Point(halfW, -halfH, -halfD));
	meshStruct.set_texcoord2D(vHandles[22], OpenMesh::Vec2f(1.f, 0.f));
	vHandles[23] = meshStruct.add_vertex(MeshStruct::Point(halfW, -halfH, halfD));
	meshStruct.set_texcoord2D(vHandles[23], OpenMesh::Vec2f(1.f, 1.f));

	//��ʼ��6���棨12�������Σ�
	std::vector<MeshStruct::VertexHandle>  face_vhandles;
	//����
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[0]);
	face_vhandles.push_back(vHandles[1]);
	face_vhandles.push_back(vHandles[2]);
	meshStruct.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[0]);
	face_vhandles.push_back(vHandles[2]);
	face_vhandles.push_back(vHandles[3]);
	meshStruct.add_face(face_vhandles);
	//�����
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[4]);
	face_vhandles.push_back(vHandles[5]);
	face_vhandles.push_back(vHandles[6]);
	meshStruct.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[4]);
	face_vhandles.push_back(vHandles[6]);
	face_vhandles.push_back(vHandles[7]);
	meshStruct.add_face(face_vhandles);
	//����
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[8]);
	face_vhandles.push_back(vHandles[9]);
	face_vhandles.push_back(vHandles[10]);
	meshStruct.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[8]);
	face_vhandles.push_back(vHandles[10]);
	face_vhandles.push_back(vHandles[11]);
	meshStruct.add_face(face_vhandles);
	//�Ҳ���
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[12]);
	face_vhandles.push_back(vHandles[13]);
	face_vhandles.push_back(vHandles[14]);
	meshStruct.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[12]);
	face_vhandles.push_back(vHandles[14]);
	face_vhandles.push_back(vHandles[15]);
	meshStruct.add_face(face_vhandles);
	//����
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[16]);
	face_vhandles.push_back(vHandles[17]);
	face_vhandles.push_back(vHandles[18]);
	meshStruct.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[16]);
	face_vhandles.push_back(vHandles[18]);
	face_vhandles.push_back(vHandles[19]);
	meshStruct.add_face(face_vhandles);
	//����
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[20]);
	face_vhandles.push_back(vHandles[21]);
	face_vhandles.push_back(vHandles[22]);
	meshStruct.add_face(face_vhandles);
	face_vhandles.clear();
	face_vhandles.push_back(vHandles[20]);
	face_vhandles.push_back(vHandles[22]);
	face_vhandles.push_back(vHandles[23]);
	meshStruct.add_face(face_vhandles);

	//���㷨����
	meshStruct.request_vertex_normals();
	meshStruct.request_face_normals();
	meshStruct.update_normals();
	meshStruct.release_face_normals();

}

void Mesh::InitSphere(float radius, int slice, int stack)
{
	meshStruct.clean();
	meshStruct.request_vertex_texcoords2D();

	int vertsPerRow = slice + 1;
	int nRows = stack - 1;

	int nVerts = vertsPerRow * nRows + 2;
	int nIndices = (nRows - 1) * slice * 6 + slice * 6;

	MeshStruct::VertexHandle* vHandles;
	vHandles = new MeshStruct::VertexHandle[nVerts];

	for (int i = 1; i <= nRows; ++i)
	{
		float phy = PI * i / stack;
		float tmpRadius = radius * sin(phy);
		for (int j = 0; j < vertsPerRow; ++j)
		{
			float theta = 2 * PI * j / slice;
			int index = (i - 1) * vertsPerRow + j;

			float x = tmpRadius * cos(theta);
			float y = radius * cos(phy);
			float z = tmpRadius * sin(theta);

			//λ������
			vHandles[index] = meshStruct.add_vertex(MeshStruct::Point(x, y, z));
			//��������
			meshStruct.set_texcoord2D(vHandles[index], OpenMesh::Vec2f(j * 1.f / slice, i * 1.f / stack));
		}
	}

	int size = vertsPerRow * nRows;
	//��Ӷ����͵ײ�����������Ϣ
	vHandles[size] = meshStruct.add_vertex(MeshStruct::Point(0.f, radius, 0.f));
	meshStruct.set_texcoord2D(vHandles[size], OpenMesh::Vec2f(0.f, 0.f));

	vHandles[size + 1] = meshStruct.add_vertex(MeshStruct::Point(0.f, -radius, 0.f));
	meshStruct.set_texcoord2D(vHandles[size + 1], OpenMesh::Vec2f(0.f, 1.f));

	int tmp(0);
	int start1 = 0;
	int start2 = nVerts - vertsPerRow - 2;
	int top = size;
	int bottom = size + 1;
	std::vector<MeshStruct::VertexHandle>  face_vhandles;
	for (int i = 0; i < slice; ++i)
	{
		face_vhandles.clear();
		face_vhandles.push_back(vHandles[top]);
		face_vhandles.push_back(vHandles[start1 + i + 1]);
		face_vhandles.push_back(vHandles[start1 + i]);
		meshStruct.add_face(face_vhandles);
	}

	for (int i = 0; i < slice; ++i)
	{
		face_vhandles.clear();
		face_vhandles.push_back(vHandles[bottom]);
		face_vhandles.push_back(vHandles[start2 + i]);
		face_vhandles.push_back(vHandles[start2 + i + 1]);
		meshStruct.add_face(face_vhandles);
	}

	for (int i = 0; i < nRows - 1; ++i)
	{
		for (int j = 0; j < slice; ++j)
		{
			face_vhandles.clear();
			face_vhandles.push_back(vHandles[i * vertsPerRow + j]);
			face_vhandles.push_back(vHandles[(i + 1) * vertsPerRow + j + 1]);
			face_vhandles.push_back(vHandles[(i + 1) * vertsPerRow + j]);
			meshStruct.add_face(face_vhandles);

			face_vhandles.clear();
			face_vhandles.push_back(vHandles[i * vertsPerRow + j]);
			face_vhandles.push_back(vHandles[i * vertsPerRow + j + 1]);
			face_vhandles.push_back(vHandles[(i + 1) * vertsPerRow + j + 1]);
			meshStruct.add_face(face_vhandles);
		}
	}

	delete[]vHandles;

	//���㷨����
	meshStruct.request_vertex_normals();
	meshStruct.request_face_normals();
	meshStruct.update_normals();
	meshStruct.release_face_normals();
}

void Mesh::InitGrid(float width, float height, int m, int n)
{
	meshStruct.clean();
	meshStruct.request_vertex_texcoords2D();

	auto nVertsRow = m + 1;			//x���򶥵���
	auto nVertsCol = n + 1;			//z���򶥵���

	auto oPosX = -width * 0.5f;			//����λ������x�������ʼλ��
	auto oPosZ = height * 0.5f;			//����λ������z�������ʼλ��

	//����λ������仯��
	auto dPosX = width / m;
	auto dPosZ = height / n;

	// ������������仯��
	auto dTexX = 1.f / m;
	auto dTexY = 1.f / n;

	MeshStruct::VertexHandle* vHandles;
	vHandles = new MeshStruct::VertexHandle[nVertsCol * nVertsRow];
	//pointsData.resize(nVertsCol * nVertsRow);

	//�����Ͻǿ�ʼ������Ӷ�����Ϣ
	for (int i = 0; i < nVertsCol; i++)
	{
		float tempZ = oPosZ - dPosZ * i;
		for (int j = 0; j < nVertsRow; j++)
		{
			int index = i * nVertsRow + j;
			//����
			vHandles[index] = meshStruct.add_vertex(MeshStruct::Point(oPosX + dPosX * j, 0.f, tempZ));
			//����
			meshStruct.set_texcoord2D(vHandles[index], OpenMesh::Vec2f(dTexX * j, dTexY * i));
		}
	}

	//һ��m*n�����ӣ�һ�����ӷ�Ϊ��������������6������
	int temp = 0;
	std::vector<MeshStruct::VertexHandle>  face_vhandles;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			face_vhandles.clear();
			face_vhandles.push_back(vHandles[i * nVertsRow + j]);
			face_vhandles.push_back(vHandles[i * nVertsRow + j + 1]);
			face_vhandles.push_back(vHandles[(i + 1) * nVertsRow + j]);
			meshStruct.add_face(face_vhandles);

			face_vhandles.clear();
			face_vhandles.push_back(vHandles[i * nVertsRow + j + 1]);
			face_vhandles.push_back(vHandles[(i + 1) * nVertsRow + j + 1]);
			face_vhandles.push_back(vHandles[(i + 1) * nVertsRow + j]);
			meshStruct.add_face(face_vhandles);
		}
	}

	delete[] vHandles;

	//���㷨����
	meshStruct.request_vertex_normals();
	meshStruct.request_face_normals();
	meshStruct.update_normals();
	meshStruct.release_face_normals();

}
