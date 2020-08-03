#pragma once
//与OpenGLshader配置相关的各种变量和方法

#include"ShaderDataInitTool.h"
#include"Transform.h"
#include"PublicStruct.h"
#include"Camera.h"
using namespace std;



class ShaderData
{
public:
	//物体的坐标属性
	mat4x4 world;					//世界矩阵
	mat4x4 worldViewProj;			//最终坐标转换矩阵
	mat4x4 worldInvTranspose;		//用来将法向量转换到世界空间

	// 临时灯光，只有定死的位置和颜色属性（以后添加灯光类）**-**
	vec3 lightPos;
	vec3 lightColor;

	//物体的VAO、VBO编号
	GLuint VAO;
	GLuint VBO;
	GLuint IndexBuffer;

	GLint drawType;					//顶点buffer的绘制方式
	GLint drawUnitNumber;			//绘制单元的数量
public:
	ShaderData()
	{
		world = mat4(0);
		worldViewProj = mat4(0);
		worldInvTranspose = mat4(0);
		drawType = GL_TRIANGLES;
		lightPos = vec3(-3, 5, 1);
		lightColor = vec3(400);
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

class PBRShaderData :public ShaderData
{
public:
	//物体的贴图编号（不一定全都需要）
	bool bUseTexture;
	GLuint tAlbedo;					//反射贴图（基础颜色）
	bool bAlbedo;
	GLuint tMetallic;				//金属度贴图
	bool bMetallic;
	GLuint tRoughness;				//粗糙贴图
	bool bRoughness;
	GLuint tAo;						//环境贴图
	bool bAo;
	GLuint tNormal;					//法线贴图
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
		auto tool = ShaderDataInitTool::GetShaderDataInitTool();
		switch (type)
		{
		case ALBEDO:
			tool.InitTextureWithFile(tAlbedo, texPath);
			break;
		case METALLIC:
			tool.InitTextureWithFile(tMetallic, texPath);
			break;
		case ROUGHNESS:
			tool.InitTextureWithFile(tRoughness, texPath);
			break;
		case AO:
			tool.InitTextureWithFile(tAo, texPath);
			break;
		case NORMAL:
			tool.InitTextureWithFile(tNormal, texPath);
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
