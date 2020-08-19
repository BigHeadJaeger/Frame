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
	//�����VAO��VBO���
	GLuint VAO;
	GLuint VBO;
	GLuint IndexBuffer;

	GLint drawType;					//����buffer�Ļ��Ʒ�ʽ
	GLint drawUnitNumber;			//���Ƶ�Ԫ������

	bool isLighting;				// �Ƿ���ܹ���
	bool isShadow;					// �Ƿ������Ӱ
private:
	void InitVertexBuffer(VertexData& vertexData);
public:
	MeshRenderer()
	{
		// Ĭ������
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

