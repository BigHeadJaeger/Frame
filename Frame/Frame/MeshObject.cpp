#include"MeshObject.h"

void MeshObject::GetVertexDataArray()
{
	
	for (auto f_it = mesh.faces_begin(); f_it != mesh.faces_end(); f_it++)
	{
		for (auto fv_ccwit = mesh.fv_iter(*f_it); fv_ccwit.is_valid(); fv_ccwit++)
		{
			vertexData.setState(STATE_TYPE_POSITION, true);
			vertexData.setLocation(STATE_TYPE_POSITION, 0);
			vertexData.position.push_back(vec3(mesh.point(*fv_ccwit).data()[0], mesh.point(*fv_ccwit).data()[1], mesh.point(*fv_ccwit).data()[2]));
			vertexData.setState(STATE_TYPE_NORMAL, true);
			vertexData.setLocation(STATE_TYPE_NORMAL, 1);
			vertexData.normal.push_back(vec3(mesh.normal(*fv_ccwit).data()[0], mesh.normal(*fv_ccwit).data()[1], mesh.normal(*fv_ccwit).data()[2]));
			//vertexData.normal.push_back(vec3(1, 1, 0));
			vertexData.setState(STATE_TYPE_TEXCOORD, true);
			vertexData.setLocation(STATE_TYPE_TEXCOORD, 2);
			vertexData.texcoord.push_back(vec2(mesh.texcoord2D(*fv_ccwit).data()[0], mesh.texcoord2D(*fv_ccwit).data()[1]));
			vertexData.setState(STATE_TYPE_COLOR, true);
			vertexData.setLocation(STATE_TYPE_COLOR, 3);
			vertexData.color.push_back(vec4(1, 1, 0, 1));
		}
	}
}

void MeshObject::readObjFile(string fileName)
{
	mesh.request_vertex_normals();

	OpenMesh::IO::Options opt;
	if (!OpenMesh::IO::read_mesh(mesh, fileName), opt)
	{
		cout << "init mesh failed" << endl;
	}

	if (!opt.check(OpenMesh::IO::Options::VertexNormal))
	{
		mesh.request_face_normals();
		mesh.update_normals();
		mesh.release_face_normals();

	}

	mesh.request_vertex_texcoords2D();

	//UE4ShaderData* temp = dynamic_cast<UE4ShaderData*>(shaderData);
	//if (temp == NULL)
	//{
	//	cout << "shaderData ptr convert to UE4ShaderData fail" << endl;
	//	return;
	//}
	//if (!opt.check(OpenMesh::IO::Options::VertexTexCoord))
	//	temp->bUseTexture = false;
	//else
	//{
	//	temp->bUseTexture = true;
	//	mesh.request_vertex_texcoords2D();
	//}

	//GetVertexDataArray();
}

void MeshObject::InitBufferData()
{
	shaderData->drawUnitNumber = mesh.n_faces() * 3;
	vertexData.totalVertex = mesh.n_faces() * 3;
	vertexData.initMemory(vertexData.totalVertex);
	//vector<float> data;
	//GetVertexDataArray(data);

	//将读取到的顶点信息变换到通用的vertexData结构体中
	GetVertexDataArray();
	shaderData->InitVertexBuffer(vertexData);
}

void MeshObject::Update(float dt)
{
	shaderData->UpdateMatrix(transformation);
}

void MeshObject::Draw()
{
	renderer->Render(shaderData);
}