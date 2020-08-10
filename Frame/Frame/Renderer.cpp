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
	tool.SetUniform("light.color", data->lightColor / vec3(255), shaderProgram);
	glBindVertexArray(0);
}

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
