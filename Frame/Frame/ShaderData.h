#pragma once
// shaderdata只有物体自身的属性，像光照这种对物体有影响但是不属于物体自身属性的值存在别处，但在renderer中传入着色器
//与OpenGLshader配置相关的各种变量和方法
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

	bool isLighting;				// 是否接受光照
	bool isShadow;					// 是否接受阴影
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

// 默认的shader数据，是一个必须包含material的shaderData
class DefaultShaderData : public ShaderData
{
public:
	shared_ptr<Material> material;
public:
	DefaultShaderData() { material = make_shared<PhongMaterial>(); }
	DefaultShaderData(shared_ptr<Material> _material) { material = _material; }

	// 切换材质
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
	glGenTextures(1, &texID);					//生成一个纹理ID
	glBindTexture(GL_TEXTURE_2D, texID);		//此时绑定到了默认纹理单元0处，在之后的代码中会指定绑定到具体哪个单元
	//指定贴图方法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//图片文件读取
	int width, height;
	unsigned char* pResult = SOIL_load_image(texPath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pResult);
	//生成一个mipmap
	glGenerateMipmap(GL_TEXTURE_2D);
	//解除绑定并释放
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(pResult);

}
