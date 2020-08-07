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
public:
	ShaderData()
	{
		world = mat4(0);
		worldViewProj = mat4(0);
		worldInvTranspose = mat4(0);
		drawType = GL_TRIANGLES;
		lightPos = vec3(-3, 5, 1);
		lightColor = vec3(400);
		isLighting = true;
		isShadow = true;
	}

	void UpdateMatrix(Transform& t);
	void InitVertexBuffer(VertexData& vertexData);
	template<typename T>
	void InitTextureWithFile(GLuint& texID, T&& texPath);
	virtual void Temp() {}
};

// Ĭ�ϵ�shader���ݣ���һ���������material��shaderData
class DefaultShaderData : public ShaderData
{
public:
	shared_ptr<Material> material;
public:
	DefaultShaderData() { material = make_shared<PhongMaterial>(); }
	DefaultShaderData(shared_ptr<Material> _material) { material = _material; }

	// �л�����
	void SetShaderData(shared_ptr<Material> _material)
	{
		material.reset();
		material = _material;
	}
};

enum TEXTURETYPE
{
	ALBEDO,
	METALLIC,
	ROUGHNESS,
	AO,
	NORMAL,
};

class PBRShaderData :public ShaderData
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
	PBRShaderData()
	{
		
		bUseTexture = false;
		bAlbedo = false;
		bMetallic = false;
		bRoughness = false;
		bAo = false;
		bNormal = false;
	}
	template<typename T>
	void InitTexture(TEXTURETYPE type, T&& texPath)
	{
		//auto tool = ShaderDataInitTool::GetShaderDataInitTool();
		switch (type)
		{
		case ALBEDO:
			InitTextureWithFile(tAlbedo, texPath);
			break;
		case METALLIC:
			InitTextureWithFile(tMetallic, texPath);
			break;
		case ROUGHNESS:
			InitTextureWithFile(tRoughness, texPath);
			break;
		case AO:
			InitTextureWithFile(tAo, texPath);
			break;
		case NORMAL:
			InitTextureWithFile(tNormal, texPath);
			break;
		default:
			break;
		}
	}

	template<typename T>
	void SetTextureState(T&& isUse) { bUseTexture = isUse; }
	template<typename T>
	void SetAlbedoState(T&& isUse) { bAlbedo = isUse; }
	template<typename T>
	void SetNormalState(T&& isUse) { bNormal = isUse; }
	template<typename T>
	void SetMetallicState(T&& isUse) { bMetallic = isUse; }
	template<typename T>
	void SetAOState(T&& isUse) { bAo = isUse; }
	template<typename T>
	void SetRoughnessState(T&& isUse) { bRoughness = isUse; }
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

template<typename T>
inline void ShaderData::InitTextureWithFile(GLuint& texID, T&& texPath)
{
	glGenTextures(1, &texID);					//����һ������ID
	glBindTexture(GL_TEXTURE_2D, texID);		//��ʱ�󶨵���Ĭ������Ԫ0������֮��Ĵ����л�ָ���󶨵������ĸ���Ԫ
	//ָ����ͼ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//ͼƬ�ļ���ȡ
	int width, height;
	unsigned char* pResult = SOIL_load_image(texPath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pResult);
	//����һ��mipmap
	glGenerateMipmap(GL_TEXTURE_2D);
	//����󶨲��ͷ�
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(pResult);

}
