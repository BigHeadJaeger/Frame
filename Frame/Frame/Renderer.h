#pragma once
#include"ShaderDataTool.h"
#include"Program.h"
#include"ShaderData.h"
#include"Component.h"

enum class RENDERERTYPE
{
	DEFAULT,
	SIMPLE,
	VERTEXCOLOR,
	MPS,
};

class Renderer : public Component
{
protected:
	ShaderProgram shaderProgram;
public:
	template<typename T>
	void InitProgram(T&& vt, T&& ft);

	void SetTransform(shared_ptr<Transform> transform)
	{
		auto tool = ShaderDataTool::GetInstance();
		tool.SetUniform("worldViewProj", transform->worldViewProj, shaderProgram);
		tool.SetUniform("world", transform->world, shaderProgram);
		tool.SetUniform("worldInvTranspose", transform->worldInvTranspose, shaderProgram);
	}

	virtual void Render(shared_ptr<ShaderData> data);

	//传texture到shader中
	//void SetTexture(GLuint& texId, int num, GLenum texNum, string samplerName, ShaderProgram& p);
	////根据不同类型的值用重载的方式传入shader中
	//void SetUniform(string&& valueName, mat4x4& value, ShaderProgram& p);
	//void SetUniform(string&& valueName, vec4& value, ShaderProgram& p);
	//void SetUniform(string&& valueName, vec3& value, ShaderProgram& p);
	//void SetUniform(string&& valueName, float value, ShaderProgram& p);
};

class DefaultRenderer :public Renderer
{
private:
	
public:
	DefaultRenderer()
	{

	}

	void Render(shared_ptr<ShaderData> shaderData) override
	{
		Renderer::Render(shaderData);
		auto data = dynamic_pointer_cast<DefaultShaderData>(shaderData);
		glUseProgram(shaderProgram.p);
		glBindVertexArray(data->VAO);
		data->material->Transfer(shaderProgram);
		glDrawArrays(data->drawType, 0, data->drawUnitNumber);
		glBindVertexArray(0);
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

//class VertexColorRender :public Renderer
//{
//private:
//	VertexColorRender() {}
//public:
//	static VertexColorRender& GetRenderer()
//	{
//		static VertexColorRender instance;
//		return instance;
//	}
//
//	VertexColorRender(VertexColorRender&) = delete;
//
//	void Render(shared_ptr<ShaderData> shaderData) override;
//};

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
