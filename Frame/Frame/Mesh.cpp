#include"Mesh.h"

void Mesh::readObjFile(string fileName)
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

	//PBRShaderData* temp = dynamic_cast<PBRShaderData*>(shaderData);
	//if (temp == NULL)
	//{
	//	cout << "shaderData ptr convert to PBRShaderData fail" << endl;
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
