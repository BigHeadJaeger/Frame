#include "Model.h"

bool Model::LoadModel(string _path)
{
	path = _path;
	auto index = path.find_last_of('\\');
	auto fullName = path.substr(index + 1);
	name = fullName.substr(0, fullName.find_last_of('.'));

	Assimp::Importer importer;
	auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return false;
	}

	ProcessModelNode(scene->mRootNode, scene, root);
	return true;
}

void Model::ProcessModelNode(aiNode* rootNode, const aiScene* scene, shared_ptr<MeshNode> node)
{
	// 一个子网格下可能有好几个网格，此处直接合并成一个(一般建模的情况中一个子网格就包含一个网格数据)
	vector<aiMesh*> meshArray;
	for (size_t i = 0; i < rootNode->mNumMeshes; i++)
	{
		auto mesh = scene->mMeshes[rootNode->mMeshes[i]];
		meshArray.push_back(mesh);
	}

	if (meshArray.size() > 0)
	{
		auto myMesh = ProcessModelMesh(meshArray, scene);
		node->data = myMesh;
	}
	else
		node->data = nullptr;


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
shared_ptr<Mesh> Model::ProcessModelMesh(vector<aiMesh*> meshArray, const aiScene* scene)
{
	shared_ptr<Mesh> meshObject = make_shared<Mesh>();
	string meshName = meshArray[0]->mName.data;
	meshObject->name = meshName;
	MeshStruct& meshStruct = meshObject->GetMeshStruct();
	meshStruct.clean();
	meshStruct.request_vertex_texcoords2D();
	meshStruct.request_vertex_normals();

	size_t numVertex = 0;
	for (size_t i = 0; i < meshArray.size(); i++)
		numVertex += meshArray[i]->mNumVertices;

	MeshStruct::VertexHandle* vHandles;
	vHandles = new MeshStruct::VertexHandle[numVertex];

	size_t offsetV = 0;
	size_t offsetF = 0;
	for (size_t k = 0; k < meshArray.size(); k++)
	{
		auto mesh = meshArray[k];
		
		for (size_t i = offsetV; i < mesh->mNumVertices; i++)
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

		offsetV += mesh->mNumVertices;

		// 索引
		std::vector<MeshStruct::VertexHandle>  face_vhandles;
		for (size_t i = offsetF; i < mesh->mNumFaces; i++)
		{
			face_vhandles.clear();
			auto face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
				face_vhandles.push_back(vHandles[face.mIndices[j]]);
			meshStruct.add_face(face_vhandles);
		}

		offsetF += mesh->mNumFaces;
	}

	// 材质
	auto firstMesh = meshArray[0];
	if (firstMesh->mMaterialIndex >= 0)
	{
		aiMaterial* meshMaterial = scene->mMaterials[firstMesh->mMaterialIndex];
		auto material = MaterialManager::GetInstance().CreateMaterial<PBRMaterial>(name + "_" + meshName);

		for (int i = 0; i < aiTextureType::aiTextureType_UNKNOWN; i++)
		{
			LoadMaterialTexture(meshMaterial, (aiTextureType)i, material);
		}

		meshObject->material = material;
	}

	delete[] vHandles;
	//计算法向量
	//meshStruct.request_vertex_normals();
	//meshStruct.request_face_normals();
	//meshStruct.update_normals();
	//meshStruct.release_face_normals();

	return meshObject;
}

void Model::LoadMaterialTexture(aiMaterial* mat, aiTextureType type, shared_ptr<PBRMaterial> material)
{
	if (mat->GetTextureCount(type) > 0)
	{
		decltype(auto) textureManager = TextureManager::GetInstance();
		aiString str;
		mat->GetTexture(type, 0, &str);

		string prefix = path.substr(0, path.find_last_of('\\'));
		string absolutePath = prefix +"\\" + str.C_Str();

		auto texture = textureManager.GetTexture(absolutePath);
		//return;
		switch (type)
		{
		case aiTextureType_NONE:
			material->SetTextureBase("");
			break;
		case aiTextureType_DIFFUSE:
			material->SetTextureBase(texture);
			break;
		case aiTextureType_SPECULAR:
			material->SetTextureMetallic(texture);
			break;
		case aiTextureType_AMBIENT:
			material->SetTextureAO(texture);
			break;
		case aiTextureType_EMISSIVE:
			break;
		case aiTextureType_HEIGHT:
			material->SetTextureNormal(texture);
			break;
		case aiTextureType_NORMALS:
			material->SetTextureNormal(texture);
			break;
		case aiTextureType_SHININESS:
			break;
		case aiTextureType_OPACITY:
			break;
		case aiTextureType_DISPLACEMENT:
			break;
		case aiTextureType_LIGHTMAP:
			break;
		case aiTextureType_REFLECTION:
			break;
		case aiTextureType_BASE_COLOR:
			material->SetTextureBase(texture);
			break;
		case aiTextureType_NORMAL_CAMERA:
			material->SetTextureNormal(texture);
			break;
		case aiTextureType_EMISSION_COLOR:
			break;
		case aiTextureType_METALNESS:
			material->SetTextureMetallic(texture);
			break;
		case aiTextureType_DIFFUSE_ROUGHNESS:
			material->SetTextureRoughness(texture);
			break;
		case aiTextureType_AMBIENT_OCCLUSION:
			material->SetTextureAO(texture);
			break;
		case aiTextureType_UNKNOWN:
			break;
		default:
			break;
		}

	}
}
