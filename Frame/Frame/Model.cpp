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

	ProcessModelNode(scene->mRootNode, scene, root);
}

void Model::ProcessModelNode(aiNode* rootNode, const aiScene* scene, shared_ptr<MeshNode> node)
{
	// 处理每个子节点下保存的网格索引
	//if (rootNode->mNumMeshes > 0)
	//{

	//}

	//shared_ptr<MeshNode> meshNode = make_shared<MeshNode>();
	for (size_t i = 0; i < rootNode->mNumMeshes; i++)
	{
		auto mesh = scene->mMeshes[rootNode->mMeshes[i]];
		auto myMesh = ProcessModelMesh(mesh, scene);

		node->data.push_back(myMesh);

		//parent.children.push_back(myMesh);
		//meshs.push_back(ProcessModelMesh(mesh, scene));
	}


	// 处理子节点
	for (size_t i = 0; i < rootNode->mNumChildren; i++)
	{
		shared_ptr<MeshNode> child = make_shared<MeshNode>();
		child->parent = node;
		node->children.push_back(child);
		ProcessModelNode(rootNode->mChildren[i], scene, child);
	}
}

// 网格处理
shared_ptr<Mesh> Model::ProcessModelMesh(aiMesh* mesh, const aiScene* scene)
{
	shared_ptr<Mesh> meshObject = make_shared<Mesh>();
	MeshStruct& meshStruct = meshObject->GetMeshStruct();
	meshStruct.clean();
	meshStruct.request_vertex_texcoords2D();
	meshStruct.request_vertex_normals();

	MeshStruct::VertexHandle* vHandles;
	vHandles = new MeshStruct::VertexHandle[mesh->mNumVertices];


	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		// 位置
		vHandles[i] = meshStruct.add_vertex(MeshStruct::Point(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
		// 法向量
		if (mesh->HasNormals())
		{
			meshStruct.set_normal(vHandles[i], OpenMesh::Vec3f(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		}
		// 当有纹理坐标的时候
		if (mesh->mTextureCoords[0])
		{
			meshStruct.set_texcoord2D(vHandles[i], OpenMesh::Vec2f(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
		}
		else
			meshStruct.set_texcoord2D(vHandles[i], OpenMesh::Vec2f(0));
	}

	// 索引
	std::vector<MeshStruct::VertexHandle>  face_vhandles;
	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		face_vhandles.clear();
		auto face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
			face_vhandles.push_back(vHandles[face.mIndices[j]]);
		meshStruct.add_face(face_vhandles);
	}

	// 材质


	delete[] vHandles;
	//计算法向量
	//meshStruct.request_vertex_normals();
	//meshStruct.request_face_normals();
	//meshStruct.update_normals();
	//meshStruct.release_face_normals();

	return meshObject;
}