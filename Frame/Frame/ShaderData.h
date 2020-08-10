#pragma once
// shaderdataֻ��������������ԣ���������ֶ�������Ӱ�쵫�ǲ����������������Ե�ֵ���ڱ𴦣�����renderer�д�����ɫ��
//��OpenGLshader������صĸ��ֱ����ͷ���
#include<glad/glad.h>
#include<SOIL.h>
#include<memory>
//#include"ShaderDataInitTool.h"
#include"Transform.h"
#include"PublicStruct.h"
#include"Camera.h"
#include"VertexData.h"
#include"Material.h"
using namespace std;

enum class SHADERDATA_TYPE
{
	DEFAULT_SHADERDATA,
	PBR_SHADERDATA,
	SIMPLE_SHADERDATA,
	VERTEX_SHADERDATA
};

class ShaderData
{
public:
	//�������������
	mat4x4 world;					//�������
	mat4x4 worldViewProj;			//��������ת������
	mat4x4 worldInvTranspose;		//������������ת��������ռ�

	// ��ʱ�ƹ⣬ֻ�ж�����λ�ú���ɫ���ԣ��Ժ���ӵƹ��ࣩ**-**
	vec3 lightPos;
	vec3 lightColor;

	//�����VAO��VBO���
	GLuint VAO;
	GLuint VBO;
	GLuint IndexBuffer;

	GLint drawType;					//����buffer�Ļ��Ʒ�ʽ
	GLint drawUnitNumber;			//���Ƶ�Ԫ������

	bool isLighting;				// �Ƿ���ܹ���
	bool isShadow;					// �Ƿ������Ӱ

	SHADERDATA_TYPE type;
public:
	ShaderData()
	{
		world = mat4(0);
		worldViewProj = mat4(0);
		worldInvTranspose = mat4(0);
		drawType = GL_TRIANGLES;
		lightPos = vec3(-3, 5, 1);
		lightColor = vec3(255);
		isLighting = true;
		isShadow = true;
	}

	void UpdateMatrix(Transform& t);
	void InitVertexBuffer(VertexData& vertexData);
	virtual void temp(){}
};

// Ĭ�ϵ�shader���ݣ���һ���������material��shaderData
class DefaultShaderData : public ShaderData
{
public:
	shared_ptr<Material> material;
public:
	DefaultShaderData()
	{
		type = SHADERDATA_TYPE::DEFAULT_SHADERDATA;
		material = make_shared<PhongMaterial>(); 
	}
	DefaultShaderData(shared_ptr<Material> _material) { material = _material; }

	// �л�����
	void SetMaterial(shared_ptr<Material> _material)
	{
		material.reset();
		material = _material;
	}
};

//class SimpleShaderData :public ShaderData
//{
//public:
//	vec3 color;
//public:
//	SimpleShaderData()
//	{
//
//	}
//	template<typename T>
//	void SetColor(T&& _color)
//	{
//		color = _color;
//	}
//};

class VertexShaderData :public ShaderData
{
public:
	VertexShaderData()
	{
		type = SHADERDATA_TYPE::VERTEX_SHADERDATA;
	}
};
