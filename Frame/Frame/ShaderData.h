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

// 默认的shader数据，是一个必须包含material的shaderData
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

	// 切换材质
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
