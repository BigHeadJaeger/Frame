#include "ShaderData.h"

void ShaderData::UpdateMatrix(Transform& t)
{
	world = translate(mat4(1.0), t.position);
	world = scale(world, t.scaler);
	if (t.rotation.x != 0)
		world = rotate(world, t.rotation.x, vec3(1.0, 0.0, 0.0));
	if (t.rotation.y != 0)
		world = rotate(world, t.rotation.y, vec3(0.0, 1.0, 0.0));
	if (t.rotation.z != 0)
		world = rotate(world, t.rotation.z, vec3(0.0, 0.0, 1.0));
	worldInvTranspose = transpose(inverse(world));
	worldViewProj = MainCamera::GetInstance().pro * MainCamera::GetInstance().view * world;
}

void ShaderData::InitVertexBuffer(VertexData& vertexData)
{
	//auto tool = ShaderDataInitTool::GetShaderDataInitTool();
	//tool.InitVertexBuffer(VAO, VBO, vertexData);
	glDeleteVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//创建顶点buffer
	glDeleteBuffers(1, &VBO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);					//先绑定，在用VAO传值时，就传送的是当前绑定的buffer

	GLsizeiptr sumSize = vertexData.position.size() * sizeof(vec3) + vertexData.normal.size() * sizeof(vec3) + vertexData.texcoord.size() * sizeof(vec2) + vertexData.color.size() * sizeof(vec4);
	//开辟空间
	glBufferData(GL_ARRAY_BUFFER, sumSize, NULL, GL_STATIC_DRAW);

	GLintptr offset = 0;

	for (auto state_it = vertexData.propertyState.begin(); state_it != vertexData.propertyState.end(); state_it++)
	{
		if ((*state_it).second.isEnable)
		{
			GLintptr size = 0;
			switch ((*state_it).first)
			{
			case STATE_TYPE_POSITION:
				size = vertexData.position.size() * sizeof(vec3);
				glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertexData.position[0]);

				glEnableVertexAttribArray((*state_it).second.location);
				glVertexAttribPointer((*state_it).second.location, 3, GL_FLOAT, GL_FALSE, 0, (void*)offset);

				offset += size;
				break;
			case STATE_TYPE_NORMAL:
				size = vertexData.normal.size() * sizeof(vec3);
				glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertexData.normal[0]);

				glEnableVertexAttribArray((*state_it).second.location);
				glVertexAttribPointer((*state_it).second.location, 3, GL_FLOAT, GL_FALSE, 0, (void*)offset);

				offset += size;
				break;
			case STATE_TYPE_TEXCOORD:
				size = vertexData.texcoord.size() * sizeof(vec2);
				glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertexData.texcoord[0]);

				glEnableVertexAttribArray((*state_it).second.location);
				glVertexAttribPointer((*state_it).second.location, 2, GL_FLOAT, GL_FALSE, 0, (void*)offset);

				offset += size;
				break;
			case STATE_TYPE_COLOR:
				size = vertexData.color.size() * sizeof(vec4);
				glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertexData.color[0]);

				glEnableVertexAttribArray((*state_it).second.location);
				glVertexAttribPointer((*state_it).second.location, 4, GL_FLOAT, GL_FALSE, 0, (void*)offset);

				offset += size;
				break;
			default:
				break;
			}
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}

//void PBRShaderData::InitTexture(TEXTURETYPE& type, string& texPath)
//{
//	ShaderDataInitTool* tool = ShaderDataInitTool::GetShaderDataInitTool();
//	switch (type)
//	{
//	case ALBEDO:
//		tool->InitTextureWithFile(tAlbedo, texPath);
//		break;
//	case METALLIC:
//		tool->InitTextureWithFile(tMetallic, texPath);
//		break;
//	case ROUGHNESS:
//		tool->InitTextureWithFile(tRoughness, texPath);
//		break;
//	case AO:
//		tool->InitTextureWithFile(tAo, texPath);
//		break;
//	case NORMAL:
//		tool->InitTextureWithFile(tNormal, texPath);
//		break;
//	default:
//		break;
//	}
//}
