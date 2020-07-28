#pragma once
//��OpenGLshader������صĸ��ֱ����ͷ���

#include"ShaderDataInitTool.h"
#include"Transform.h"
#include"PublicStruct.h"
#include"Camera.h"
using namespace std;



class ShaderData
{
public:
	//�������������
	mat4x4 world;					//�������
	mat4x4 worldViewProj;			//��������ת������
	mat4x4 worldInvTranspose;		//������������ת��������ռ�

	//�����VAO��VBO���
	GLuint VAO;
	GLuint VBO;
	GLuint IndexBuffer;

	GLint drawType;					//����buffer�Ļ��Ʒ�ʽ
	GLint drawUnitNumber;			//���Ƶ�Ԫ������
public:
	ShaderData()
	{
		world = mat4(0);
		worldViewProj = mat4(0);
		worldInvTranspose = mat4(0);
		drawType = GL_TRIANGLES;
	}

	void UpdateMatrix(Transform& t);
	void InitVertexBuffer(VertexData& vertexData);
	virtual void Temp() {}
};

enum TEXTURETYPE
{
	ALBEDO,
	METALLIC,
	ROUGHNESS,
	AO,
	NORMAL,
};

class UE4ShaderData :public ShaderData
{
public:
	//�������ͼ��ţ���һ��ȫ����Ҫ��
	bool bUseTexture;
	GLuint tAlbedo;					//������ͼ��������ɫ��
	bool bAlbedo;
	GLuint tMetallic;				//��������ͼ
	bool bMetallic;
	GLuint tRoughness;				//�ֲ���ͼ
	bool bRoughness;
	GLuint tAo;						//������ͼ
	bool bAo;
	GLuint tNormal;					//������ͼ
	bool bNormal;
public:
	template<typename T>
	void InitTexture(TEXTURETYPE& type, T&& texPath)
	{
		auto tool = ShaderDataInitTool::GetShaderDataInitTool();
		switch (type)
		{
		case ALBEDO:
			tool->InitTextureWithFile(tAlbedo, texPath);
			break;
		case METALLIC:
			tool->InitTextureWithFile(tMetallic, texPath);
			break;
		case ROUGHNESS:
			tool->InitTextureWithFile(tRoughness, texPath);
			break;
		case AO:
			tool->InitTextureWithFile(tAo, texPath);
			break;
		case NORMAL:
			tool->InitTextureWithFile(tNormal, texPath);
			break;
		default:
			break;
		}
	}
};

class SimpleShaderData :public ShaderData
{
public:
	vec3 color;
public:
	template<typename T>
	void SetColor(T&& _color)
	{
		color = _color;
	}
};

class VertexShaderData :public ShaderData
{
public:

};
