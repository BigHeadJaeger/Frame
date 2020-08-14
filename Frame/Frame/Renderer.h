#pragma once
#include"ShaderDataTool.h"
//#include"Program.h"
#include"Component.h"
#include"Material.h"
#include"MeshReference.h"

enum class RENDERERTYPE
{
	DEFAULT,
	SIMPLE,
	VERTEXCOLOR,
	MPS,
};

class Renderer : public Component
{
public:
	shared_ptr<Material> material;

private:

public:

	void SetTransform()
	{
		auto transform = object->GetTransform();
		auto tool = ShaderDataTool::GetInstance();
		tool.SetUniform("worldViewProj", transform->worldViewProj, material->shaderProgram);
		tool.SetUniform("world", transform->world, material->shaderProgram);
		tool.SetUniform("worldInvTranspose", transform->worldInvTranspose, material->shaderProgram);
	}

	void SetCamera()
	{

	}

	virtual void Render() = 0;

	void SetMaterial(shared_ptr<Material> _material)
	{
		if (_material == nullptr)
		{
			material.reset();
			material = make_shared<NoneMaterial>();
		}
		else
		{
			material.reset();
			material = _material;
		}
	}
};

class MeshRenderer :public Renderer
{
private:
	//物体的VAO、VBO编号
	GLuint VAO;
	GLuint VBO;
	GLuint IndexBuffer;

	GLint drawType;					//顶点buffer的绘制方式
	GLint drawUnitNumber;			//绘制单元的数量
public:
	MeshRenderer()
	{
		type = COMPONENT_MESHRENDER;
	}

	void SetMeshData()
	{
		if (object->isComponent(COMPONENT_MESHREFERENCE))
		{
			auto meshReference = dynamic_pointer_cast<MeshReference>(object->GetComponentByName(COMPONENT_MESHREFERENCE));
			meshReference->vertexData
		}
	}

	void SetLight()
	{

	}

	void Render() override
	{
		SetTransform();
		//Renderer::Render(shaderData);
		//auto data = dynamic_pointer_cast<DefaultShaderData>(shaderData);
		
		glUseProgram(material->shaderProgram.p);
		glBindVertexArray(data->VAO);
		data->material->Transfer(material->shaderProgram);
		glDrawArrays(data->drawType, 0, data->drawUnitNumber);
		glBindVertexArray(0);
	}

	MeshRenderer(MeshRenderer&);
};

