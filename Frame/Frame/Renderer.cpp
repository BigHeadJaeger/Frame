#include "Renderer.h"

void Renderer::Render(shared_ptr<ShaderData> data)
{
	glUseProgram(shaderProgram.p);
	//绑定前面设置好的VAO
	glBindVertexArray(data->VAO);
	//传递坐标变换矩阵
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
	// 父类处理共有数据
	Renderer::Render(shaderData);

	auto data = dynamic_pointer_cast<PBRShaderData>(shaderData);
	glUseProgram(shaderProgram.p);
	glBindVertexArray(data->VAO);				
	//根据参数上对纹理的选择，将需要的纹理传入着色器
	//先将是否使用纹理传入shader
	auto tool = ShaderDataTool::GetInstance();
	tool.SetUniform("useTexture", data->bUseTexture, shaderProgram);
	if (data->bUseTexture)
	{
		//基础反射贴图
		tool.SetUniform("useAlbedo", data->bAlbedo, shaderProgram);
		if (data->bAlbedo)
		{
			tool.SetTexture(data->tAlbedo, 0, GL_TEXTURE0, "albedoMap", shaderProgram);

		}

		//法线贴图
		tool.SetUniform("useNormal", data->bNormal, shaderProgram);
		if (data->bNormal)
		{
			tool.SetTexture(data->tNormal, 1, GL_TEXTURE1, "normalMap", shaderProgram);

		}

		//金属度贴图
		tool.SetUniform("useMetallic", data->bMetallic, shaderProgram);
		if (data->bMetallic)
		{
			tool.SetTexture(data->tMetallic, 2, GL_TEXTURE2, "metallicMap", shaderProgram);

		}
		else
		{
			//此处暂时直接将没有金属贴图的金属度用数字传入shader
			tool.SetUniform("metallicN", 0.2f, shaderProgram);
		}

		//粗糙贴图
		tool.SetUniform("useRoughness", data->bRoughness, shaderProgram);
		if (data->bRoughness)
		{
			tool.SetTexture(data->tRoughness, 3, GL_TEXTURE3, "roughnessMap", shaderProgram);
		}
		else
			tool.SetUniform("roughnessN", 1.0f, shaderProgram);

		//环境光ao贴图
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
//	//传递坐标变换矩阵
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
