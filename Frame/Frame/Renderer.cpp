#include "Renderer.h"
#include"Object.h"
#include"Light.h"
#include"LightComponent.h"

void MeshRenderer::InitVertexBuffer(VertexData& vertexData)
{
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

void MeshRenderer::UpdateMeshData()
{
	if (object->isComponent(COMPONENT_MESHREFERENCE))
	{
		auto meshReference = dynamic_pointer_cast<MeshReference>(object->GetComponentByName(COMPONENT_MESHREFERENCE));
		if (meshReference->meshChange)
		{
			meshReference->meshChange = false;
			InitVertexBuffer(meshReference->vertexData);
			drawUnitNumber = meshReference->vertexData.totalVertex;
		}
	}
}

void Renderer::SetTransform()
{
	auto transform = object->GetTransform();
	auto tool = ShaderDataTool::GetInstance();
	tool.SetUniform("worldViewProj", transform->worldViewProj, material->shaderProgram);
	tool.SetUniform("world", transform->world, material->shaderProgram);
	tool.SetUniform("worldInvTranspose", transform->worldInvTranspose, material->shaderProgram);
}

void Renderer::SetCamera()
{
	auto tool = ShaderDataTool::GetInstance();
	auto mainCamera = RenderFrameModel::GetInstance().GetMainCamera();
	if (mainCamera->isUseable())
	{
		tool.SetUniform("eyePos", mainCamera->object->GetTransform()->position, material->shaderProgram);
	}
}

void Renderer::SetLight()
{
	auto tool = ShaderDataTool::GetInstance();
	auto lightComponents = RenderFrameModel::GetInstance().GetLightList();
	int dirCount = 0;
	int pointCount = 0;
	for (size_t i = 0; i < lightComponents.size(); i++)
	{
		if (lightComponents[i]->isUseable())
		{
			
			switch (lightComponents[i]->light->type)
			{
			case LIGHT_TYPE::DIRECT_LIGHT:
			{
				auto light = dynamic_pointer_cast<DirLight>(lightComponents[i]->light);
				string preName = "dirLights[" + to_string(dirCount) + "].";
				dirCount++;
				tool.SetUniform((preName + "position"), lightComponents[i]->object->GetPosition(), material->shaderProgram);
				tool.SetUniform((preName + "color"), light->lightColor / vec3(255), material->shaderProgram);
				tool.SetUniform((preName + "dir"), normalize(light->lightDir), material->shaderProgram);
				break;
			}
			case LIGHT_TYPE::POINT_LIGHT:
				break;
			default:
				break;
			}
		}
	}
}
