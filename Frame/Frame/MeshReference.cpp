#include"MeshReference.h"

void MeshReference::ConvertMeshData()
{
	vertexData.Clear();
	vertexData.totalVertex = mesh->meshStruct.n_faces() * 3;
	vertexData.initMemory(vertexData.totalVertex);

	for (auto f_it = mesh->meshStruct.faces_begin(); f_it != mesh->meshStruct.faces_end(); f_it++)
	{
		for (auto fv_ccwit = mesh->meshStruct.fv_iter(*f_it); fv_ccwit.is_valid(); fv_ccwit++)
		{
			vertexData.setState(STATE_TYPE_POSITION, true);
			vertexData.setLocation(STATE_TYPE_POSITION, 0);
			vertexData.position.push_back(vec3(mesh->meshStruct.point(*fv_ccwit).data()[0], mesh->meshStruct.point(*fv_ccwit).data()[1], mesh->meshStruct.point(*fv_ccwit).data()[2]));
			vertexData.setState(STATE_TYPE_NORMAL, true);
			vertexData.setLocation(STATE_TYPE_NORMAL, 1);
			vertexData.normal.push_back(vec3(mesh->meshStruct.normal(*fv_ccwit).data()[0], mesh->meshStruct.normal(*fv_ccwit).data()[1], mesh->meshStruct.normal(*fv_ccwit).data()[2]));
			//vertexData.normal.push_back(vec3(1, 1, 0));
			vertexData.setState(STATE_TYPE_TEXCOORD, true);
			vertexData.setLocation(STATE_TYPE_TEXCOORD, 2);
			vertexData.texcoord.push_back(vec2(mesh->meshStruct.texcoord2D(*fv_ccwit).data()[0], mesh->meshStruct.texcoord2D(*fv_ccwit).data()[1]));
			vertexData.setState(STATE_TYPE_COLOR, true);
			vertexData.setLocation(STATE_TYPE_COLOR, 3);
			vertexData.color.push_back(vec4(1, 1, 0, 1));
		}
	}


}

//void MeshReference::InitBufferData()
//{
//	//shaderData->drawUnitNumber = mesh.n_faces() * 3;
//	vertexData.totalVertex = mesh.n_faces() * 3;
//	vertexData.initMemory(vertexData.totalVertex);
//	//vector<float> data;
//	//GetVertexDataArray(data);
//
//	//将读取到的顶点信息变换到通用的vertexData结构体中
//	GetVertexDataArray();
//	shaderData->InitVertexBuffer(vertexData);
//}
