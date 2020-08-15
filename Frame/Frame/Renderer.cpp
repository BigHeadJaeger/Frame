#include "Renderer.h"
#include"Object.h"

//void Renderer::Render(shared_ptr<ShaderData> data)
//{
//	glUseProgram(shaderProgram.p);
//	//绑定前面设置好的VAO
//	glBindVertexArray(data->VAO);
//	//传递坐标变换矩阵
//	auto tool = ShaderDataTool::GetInstance();
//	tool.SetUniform("worldViewProj", data->worldViewProj, shaderProgram);
//	tool.SetUniform("world", data->world, shaderProgram);
//	tool.SetUniform("worldInvTranspose", data->worldInvTranspose, shaderProgram);
//	tool.SetUniform("eyePos", MainCamera::GetInstance().eyePos, shaderProgram);
//	tool.SetUniform("light.position", data->lightPos, shaderProgram);
//	tool.SetUniform("light.color", data->lightColor / vec3(255), shaderProgram);
//	glBindVertexArray(0);
//}

//void SimpleRenderer::Render(ShaderData* shaderData)
//{
//	glUseProgram(shaderProgram.p);
//	auto data = dynamic_cast<SimpleShaderData*>(shaderData);
//	glBindVertexArray(data->VAO);
//	//传递坐标变换矩阵
//	SetUniform("worldViewProj", data->worldViewProj, shaderProgram);
//	SetUniform("world", data->world, shaderProgram);
//	SetUniform("worldInvTranspose", data->worldInvTranspose, shaderProgram);
//
//	SetUniform("color", data->color, shaderProgram);
//	glDrawArrays(data->drawType, 0, data->drawUnitNumber);
//}

//void VertexColorRender::Render(shared_ptr<ShaderData> shaderData)
//{
//	Renderer::Render(shaderData);
//
//	auto data = dynamic_pointer_cast<VertexShaderData>(shaderData);
//	glUseProgram(shaderProgram.p);
//	glBindVertexArray(data->VAO);
//	glDrawArrays(data->drawType, 0, data->drawUnitNumber);
//	glBindVertexArray(0);
//}


//PBRRenderer* PBRRenderer::instance = NULL;
//SimpleRenderer* SimpleRenderer::instance = NULL;
//MPSRenderer* MPSRenderer::instance = NULL;
//VertexColorRender* VertexColorRender::instance = NULL;
//VertexColorRender VertexColorRender::ins

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
	tool.SetUniform("eyePos", mainCamera->eyePos, material->shaderProgram);
}
