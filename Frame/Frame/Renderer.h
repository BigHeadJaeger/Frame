#pragma once
#include"ShaderDataTool.h"
#include"Component.h"
#include"Material.h"
#include"MeshReference.h"
#include"RenderFrameModel.h"
#include"Camera.h"

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
	void SetTransform();

	void SetCamera();

	void SetLight();

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

	bool isLighting;				// 是否接受光照
	bool isShadow;					// 是否接受阴影
private:
	void InitVertexBuffer(VertexData& vertexData);
public:
	MeshRenderer()
	{
		// 默认纹理
		material = make_shared<NoneMaterial>();
		type = COMPONENT_MESHRENDER;
		drawType = GL_TRIANGLES;
	}

	void UpdateMeshData();



	void Update(float dt) override
	{
		if (!isUseable())
			return;
		UpdateMeshData();
	}

	void Render() override
	{
		if (!isUseable())
			return;
		SetCamera();
		SetTransform();
		SetLight();
		glUseProgram(material->shaderProgram.p);
		glBindVertexArray(VAO);
		material->Transfer();
		glDrawArrays(drawType, 0, drawUnitNumber);
		glBindVertexArray(0);
	}
};

