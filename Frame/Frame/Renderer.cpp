#include "Renderer.h"

void Renderer::Render(shared_ptr<ShaderData> data)
{
	glUseProgram(shaderProgram.p);
	//��ǰ�����úõ�VAO
	glBindVertexArray(data->VAO);
	//��������任����
	auto tool = ShaderDataTool::GetInstance();
	tool.SetUniform("worldViewProj", data->worldViewProj, shaderProgram);
	tool.SetUniform("world", data->world, shaderProgram);
	tool.SetUniform("worldInvTranspose", data->worldInvTranspose, shaderProgram);
	tool.SetUniform("eyePos", MainCamera::GetInstance().eyePos, shaderProgram);
	tool.SetUniform("light.position", data->lightPos, shaderProgram);
	tool.SetUniform("light.color", data->lightColor, shaderProgram);
	glBindVertexArray(0);
}

void PBRRenderer::Render(shared_ptr<ShaderData> shaderData)
{
	// ���ദ��������
	Renderer::Render(shaderData);

	auto data = dynamic_pointer_cast<PBRShaderData>(shaderData);
	glUseProgram(shaderProgram.p);
	glBindVertexArray(data->VAO);				
	//���ݲ����϶������ѡ�񣬽���Ҫ����������ɫ��
	//�Ƚ��Ƿ�ʹ��������shader
	auto tool = ShaderDataTool::GetInstance();
	tool.SetUniform("useTexture", data->bUseTexture, shaderProgram);
	if (data->bUseTexture)
	{
		//����������ͼ
		tool.SetUniform("useAlbedo", data->bAlbedo, shaderProgram);
		if (data->bAlbedo)
		{
			tool.SetTexture(data->tAlbedo, 0, GL_TEXTURE0, "albedoMap", shaderProgram);

		}

		//������ͼ
		tool.SetUniform("useNormal", data->bNormal, shaderProgram);
		if (data->bNormal)
		{
			tool.SetTexture(data->tNormal, 1, GL_TEXTURE1, "normalMap", shaderProgram);

		}

		//��������ͼ
		tool.SetUniform("useMetallic", data->bMetallic, shaderProgram);
		if (data->bMetallic)
		{
			tool.SetTexture(data->tMetallic, 2, GL_TEXTURE2, "metallicMap", shaderProgram);

		}
		else
		{
			//�˴���ʱֱ�ӽ�û�н�����ͼ�Ľ����������ִ���shader
			tool.SetUniform("metallicN", 0.2f, shaderProgram);
		}

		//�ֲ���ͼ
		tool.SetUniform("useRoughness", data->bRoughness, shaderProgram);
		if (data->bRoughness)
		{
			tool.SetTexture(data->tRoughness, 3, GL_TEXTURE3, "roughnessMap", shaderProgram);
		}
		else
			tool.SetUniform("roughnessN", 1.0f, shaderProgram);

		//������ao��ͼ
		tool.SetUniform("useAO", data->bAo, shaderProgram);
		if (data->bAo)
		{
			tool.SetTexture(data->tAo, 4, GL_TEXTURE4, "aoMap", shaderProgram);

		}
	}

	glDrawArrays(data->drawType, 0, data->drawUnitNumber);

	glBindVertexArray(0);

}
//
//void SimpleRenderer::Render(ShaderData* shaderData)
//{
//	glUseProgram(shaderProgram.p);
//	auto data = dynamic_cast<SimpleShaderData*>(shaderData);
//	glBindVertexArray(data->VAO);
//	//��������任����
//	SetUniform("worldViewProj", data->worldViewProj, shaderProgram);
//	SetUniform("world", data->world, shaderProgram);
//	SetUniform("worldInvTranspose", data->worldInvTranspose, shaderProgram);
//
//	SetUniform("color", data->color, shaderProgram);
//	glDrawArrays(data->drawType, 0, data->drawUnitNumber);
//}

void VertexColorRender::Render(shared_ptr<ShaderData> shaderData)
{
	Renderer::Render(shaderData);

	auto data = dynamic_pointer_cast<VertexShaderData>(shaderData);
	glUseProgram(shaderProgram.p);
	glBindVertexArray(data->VAO);
	glDrawArrays(data->drawType, 0, data->drawUnitNumber);
	glBindVertexArray(0);
}


//PBRRenderer* PBRRenderer::instance = NULL;
//SimpleRenderer* SimpleRenderer::instance = NULL;
//MPSRenderer* MPSRenderer::instance = NULL;
//VertexColorRender* VertexColorRender::instance = NULL;
//VertexColorRender VertexColorRender::ins
