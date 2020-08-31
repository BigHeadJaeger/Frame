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
	auto meshReference = object.lock()->GetComponent<MeshReference>();
	if (meshReference)
	{
		if (meshReference->meshChange)
		{
			meshReference->meshChange = false;
			InitVertexBuffer(meshReference->vertexData);
			drawUnitNumber = meshReference->vertexData.totalVertex;
		}
	}
}

void Renderer::SetTransform(shared_ptr<ShaderProgram> shader)
{
	shared_ptr<Transform> transform = object.lock()->transform;
	//auto transform = object.lock()->transform;
	decltype(auto) tool = ShaderDataTool::GetInstance();
	tool.SetUniform("worldViewProj", transform->worldViewProj, shader);
	tool.SetUniform("world", transform->world, shader);
	tool.SetUniform("worldInvTranspose", transform->worldInvTranspose, shader);
}

void Renderer::SetCamera(shared_ptr<ShaderProgram> shader)
{
	decltype(auto) tool = ShaderDataTool::GetInstance();
	auto mainCamera = RenderFrameModel::GetInstance().GetMainCamera();
	if (mainCamera->isUseable())
	{
		tool.SetUniform("eyePos", mainCamera->object.lock()->transform->position, shader);
	}
}

void Renderer::SetLight(shared_ptr<ShaderProgram> shader)
{
	decltype(auto) tool = ShaderDataTool::GetInstance();
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
				tool.SetUniform(preName + "isAble", true, shader);
				tool.SetUniform((preName + "position"), lightComponents[i]->object.lock()->GetPosition(), shader);
				tool.SetUniform((preName + "color"), light->lightColor / vec3(255), shader);
				tool.SetUniform((preName + "dir"), normalize(light->lightDir), shader);
				break;
			}
			case LIGHT_TYPE::POINT_LIGHT:
			{
				auto light = dynamic_pointer_cast<PointLight>(lightComponents[i]->light);
				string preName = "pointLights[" + to_string(pointCount) + "].";
				pointCount++;
				tool.SetUniform(preName + "isAble", true, shader);
				tool.SetUniform((preName + "position"), lightComponents[i]->object.lock()->GetPosition(), shader);
				tool.SetUniform((preName + "color"), light->lightColor / vec3(255), shader);
				tool.SetUniform((preName + "radius"), light->radius, shader);
				tool.SetUniform((preName + "constant"), light->constant, shader);
				tool.SetUniform((preName + "linear"), light->linear, shader);
				tool.SetUniform((preName + "quadratic"), light->quadratic, shader);
				break;
			}
			default:
				break;
			}
		}
	}
}

void MeshRenderer::DrawObject()
{
	auto shader = material->shader.lock();
	glUseProgram(shader->p);
	glBindVertexArray(VAO);
	SetCamera(shader);
	SetTransform(shader);
	SetLight(shader);
	material->Transfer();
	glDrawArrays(drawType, 0, drawUnitNumber);
	glBindVertexArray(0);
	glUseProgram(0);
}

void MeshRenderer::Render()
{
	if (!isUseable())
		return;
	auto objPtr = object.lock();

	if (objPtr->isSelect)
	{
		
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		DrawObject();

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		// 将物体放大1.02倍进行绘制
		auto orScaler = objPtr->transform->scaler;
		objPtr->transform->SetScaler(orScaler * 1.02f);
		objPtr->transform->UpdateMatrix();
		auto shader = ShaderManager::GetInstance().GetShader("SF_Outline");
		glUseProgram(shader->p);
		glBindVertexArray(VAO);
		SetCamera(shader);
		SetTransform(shader);
		glDrawArrays(drawType, 0, drawUnitNumber);
		glBindVertexArray(0);
		glUseProgram(0);
		objPtr->transform->SetScaler(orScaler);
	}
	else
	{
		DrawObject();
	}

	// 一些状态的复位
	glStencilMask(0xFF);		// 开启写入，否则无法进行清理
	glDisable(GL_BLEND);
}