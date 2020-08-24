#include "Model.h"

void Model::LoadModel(string path)
{
	Assimp::Importer importer;
	auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}
	//meshStruct.clean();
	//meshStruct.request_vertex_texcoords2D();

	ProcessModelNode(scene->mRootNode, scene);
}

void Model::ProcessModelNode(aiNode* rootNode, const aiScene* scene)
{
	// ����ÿ���ӽڵ��±������������
	for (size_t i = 0; i < rootNode->mNumMeshes; i++)
	{
		auto mesh = scene->mMeshes[rootNode->mMeshes[i]];
		meshs.push_back(ProcessModelMesh(mesh, scene));
	}

	// �����ӽڵ�
	for (size_t i = 0; i < rootNode->mNumChildren; i++)
	{
		ProcessModelNode(rootNode->mChildren[i], scene);
	}
}

// ������
Mesh Model::ProcessModelMesh(aiMesh* mesh, const aiScene* scene)
{
	Mesh meshObject;
	MeshStruct& meshStruct = meshObject.GetMeshStruct();
	meshStruct.clean();
	meshStruct.request_vertex_texcoords2D();
	meshStruct.request_vertex_normals();

	MeshStruct::VertexHandle* vHandles;
	vHandles = new MeshStruct::VertexHandle[mesh->mNumVertices];


	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		// λ��
		vHandles[i] = meshStruct.add_vertex(MeshStruct::Point(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
		// ������
		if (mesh->HasNormals())
		{
			meshStruct.set_normal(vHandles[i], OpenMesh::Vec3f(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		}
		// �������������ʱ��
		if (mesh->mTextureCoords[0])
		{
			meshStruct.set_texcoord2D(vHandles[i], OpenMesh::Vec2f(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
		}
		else
			meshStruct.set_texcoord2D(vHandles[i], OpenMesh::Vec2f(0));
	}

	// ����
	std::vector<MeshStruct::VertexHandle>  face_vhandles;
	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		face_vhandles.clear();
		auto face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
			face_vhandles.push_back(vHandles[face.mIndices[j]]);
		meshStruct.add_face(face_vhandles);
	}

	// ����


	delete[] vHandles;
	//���㷨����
	//meshStruct.request_vertex_normals();
	//meshStruct.request_face_normals();
	//meshStruct.update_normals();
	//meshStruct.release_face_normals();

	return meshObject;
}