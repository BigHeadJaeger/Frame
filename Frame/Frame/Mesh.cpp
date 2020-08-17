#include"Mesh.h"

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
