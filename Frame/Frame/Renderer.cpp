#include "Renderer.h"
#include"Object.h"
#include"Light.h"
#include"LightComponent.h"

void MeshRenderer::UpdateMeshData()
{
	auto meshReference = object.lock()->GetComponent<MeshReference>();
	if (meshReference)
	{
		if (meshReference->meshChange)
		{
			meshReference->meshChange = false;
			ShaderDataTool::GetInstance().InitVertexBuffer(meshReference->vertexData, meshReference->vertexData.VAO, meshReference->vertexData.VBO);
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
	auto meshReference = object.lock()->GetComponent<MeshReference>();
	if (!meshReference)
		return;

	glBindVertexArray(meshReference->vertexData.VAO);
	SetCamera(shader);
	SetTransform(shader);
	SetLight(shader);

	material->Transfer();
	glDrawArrays(meshReference->vertexData.drawType, 0, meshReference->vertexData.totalVertex);
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
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
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
		auto meshReference = object.lock()->GetComponent<MeshReference>();
		if (!meshReference)
			return;
		glBindVertexArray(meshReference->vertexData.VAO);
		//glBindVertexArray(VAO);
		SetCamera(shader);
		SetTransform(shader);
		//glDrawArrays(drawType, 0, drawUnitNumber);
		glDrawArrays(meshReference->vertexData.drawType, 0, meshReference->vertexData.totalVertex);
		glBindVertexArray(0);
		glUseProgram(0);
		objPtr->transform->SetScaler(orScaler);
		glStencilMask(0xFF);			// 开启写入，否则无法进行清理
		glClear(GL_STENCIL_BUFFER_BIT);	// 清理模板值，这样可以使每个物体有一个独立的选中框
		glDisable(GL_STENCIL_TEST);		// 关闭模板测试
	}
	else
	{
		DrawObject();
	}

	// 一些状态的复位
	glDisable(GL_BLEND);
}