#pragma once
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
using namespace glm;
using namespace std;
#include"Program.h"
#include"ShaderData.h"

enum RENDERERTYPE
{
	PBR,
	SIMPLE,
	VERTEXCOLOR,
	MPS,
};

class Renderer
{
protected:
	ShaderProgram shaderProgram;
public:
	template<typename T>
	void InitProgram(T&& vt, T&& ft);

	virtual void Render(shared_ptr<ShaderData> data);

	//传texture到shader中
	void SetTexture(GLuint& texId, int num, GLenum texNum, string samplerName, ShaderProgram& p);
	//根据不同类型的值用重载的方式传入shader中
	void SetUniform(string&& valueName, mat4x4& value, ShaderProgram& p);
	void SetUniform(string&& valueName, vec4& value, ShaderProgram& p);
	void SetUniform(string&& valueName, vec3& value, ShaderProgram& p);
	void SetUniform(string&& valueName, float value, ShaderProgram& p);
};

class DefaultRenderer :public Renderer
{
private:
	DefaultRenderer()
	{

	}
public:
	static DefaultRenderer& GetRenderer()
	{
		static DefaultRenderer instance;
		return instance;
	}

	void Render(shared_ptr<ShaderData> shaderData) override
	{
		auto data = dynamic_pointer_cast<DefaultShaderData>(shaderData);
		//data->material
	}

	DefaultRenderer(DefaultRenderer&) = delete;
};

//class SimpleRenderer :public Renderer
//{
//private:
//	static SimpleRenderer* instance;
//	SimpleRenderer() {}
//public:
//	static SimpleRenderer* GetRenderer()
//	{
//		if (instance == NULL)
//		{
//			instance = new SimpleRenderer();
//		}
//		return instance;
//	}
//
//	void Render(unique_ptr<ShaderData> shaderData)override;
//};

//不同的渲染器只需要一个，所以都设为单例
//class PBRRenderer :public Renderer
//{
//private:
//	static PBRRenderer* instance;
//	PBRRenderer() {}
//public:
//	static PBRRenderer* GetRenderer()
//	{
//		if (instance == NULL)
//		{
//			instance = new PBRRenderer();
//		}
//		return instance;
//	}
//	void Render(unique_ptr<ShaderData> shaderData) override;
//};

class PBRRenderer :public Renderer
{
private:
	PBRRenderer() 
	{

	}
public:
	static PBRRenderer& GetRenderer()
	{
		static PBRRenderer instance;
		return instance;
	}

	void Render(shared_ptr<ShaderData> shaderData) override;

	PBRRenderer(PBRRenderer&) = delete;
};

//class VertexColorRender :public Renderer
//{
//private:
//	static shared_ptr<VertexColorRender> instance;
//	VertexColorRender() = delete;
//public:
//	static shared_ptr<VertexColorRender> GetRenderer()
//	{
//		if (instance == NULL)
//			instance = make_shared(new VertexColorRender());
//		return instance;
//	}
//
//	void Render(shared_ptr<ShaderData> shaderData) override;
//};

class VertexColorRender :public Renderer
{
private:
	VertexColorRender() {}
public:
	static VertexColorRender& GetRenderer()
	{
		static VertexColorRender instance;
		return instance;
	}

	VertexColorRender(VertexColorRender&) = delete;

	void Render(shared_ptr<ShaderData> shaderData) override;
};

//class MPSRenderer:public Renderer
//{
//private:
//	static MPSRenderer* instance;
//	MPSRenderer() {}
//public:
//	static MPSRenderer* GetRenderer()
//	{
//		if (instance == NULL)
//		{
//			instance = new MPSRenderer();
//		}
//		return instance;
//	}
//	void Render(ShaderData* shaderData) override;
//};

template<typename T>
inline void Renderer::InitProgram(T&& vt, T&& ft)
{
	shaderProgram.SetShader(vt, ft);
}
