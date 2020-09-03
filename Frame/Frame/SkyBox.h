#pragma once
#include<glad/glad.h>
#include<iostream>
#include<string>

#include"Material.h"
#include"ShaderManager.h"
#include"VertexData.h"
#include"Mesh.h"

class SkyBox
{
public:
	Mesh box;
	VertexData vertexData;
	weak_ptr<SkyBoxMaterial> material;
public:
	SkyBox()
	{


	}

	void InitSkyBox(shared_ptr<SkyBoxMaterial> _material)
	{
		material = _material;

		box.InitBox(2, 2, 2);
		ConvertMeshData();
		ShaderDataTool::GetInstance().InitVertexBuffer(vertexData, vertexData.VAO, vertexData.VBO);
	}

	// 绘制天空盒
	void Render()
	{
		decltype(auto) tool = ShaderDataTool::GetInstance();
		auto mainCamera = RenderFrameModel::GetInstance().GetMainCamera();
		glDepthMask(GL_FALSE);
		glDisable(GL_CULL_FACE);
		auto shader = ShaderManager::GetInstance().GetShader("SF_SkyBox");
		glUseProgram(shader->p);
		glBindVertexArray(vertexData.VAO);

		mat4 world;
		world = translate(mat4(1), mainCamera->object.lock()->transform->position);
		auto view = mat4(mat3(mainCamera->view));
		tool.SetUniform("view", view, shader);
		tool.SetUniform("projection", mainCamera->pro, shader);
		
		material.lock()->Transfer();

		glDrawArrays(vertexData.drawType, 0, vertexData.totalVertex);
		glBindVertexArray(0);
		glUseProgram(0);
		glDepthMask(GL_TRUE);
	}
private:
	// 将网格数据转化为openg使用的顶点数据
	void ConvertMeshData()
	{
		vertexData.Clear();
		vertexData.totalVertex = box.meshStruct.n_faces() * 3;
		vertexData.initMemory(vertexData.totalVertex);
		for (auto f_it = box.meshStruct.faces_begin(); f_it != box.meshStruct.faces_end(); f_it++)
		{
			for (auto fv_ccwit = box.meshStruct.fv_iter(*f_it); fv_ccwit.is_valid(); fv_ccwit++)
			{
				vertexData.setState(STATE_TYPE_POSITION, true);
				vertexData.setLocation(STATE_TYPE_POSITION, 0);
				vertexData.position.push_back(vec3(box.meshStruct.point(*fv_ccwit).data()[0], box.meshStruct.point(*fv_ccwit).data()[1], box.meshStruct.point(*fv_ccwit).data()[2]));
			}
		}
	}
};