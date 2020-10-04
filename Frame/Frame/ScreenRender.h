// 处理屏幕渲染
#pragma once
#include<iostream>
#include<string>
#include<glad/glad.h>
#include<functional>
#include"Const.h"
#include"ShaderDataTool.h"
#include"ShaderManager.h"
#include"Texture2D.h"

enum class SCREEN_RENDER_TYPE
{
	NONE = 0,
	INVERSE_COLOR,
	GRAY,
	KERNEL
};

class ScreenRender
{
public:
	GLuint FBO;
	shared_ptr<Texture2D> texColorAttach;
	GLuint DSRenderBuffer;				// 深度和模板的RBO

	GLuint multiSampledBuffer;			// 多重采样的缓冲
	GLuint multiSampledColorBuffer;		// 多重采样的纹理附件
	GLuint multiSampledRenderBuffer;	// 多重采样的深度和模板的RBO


	// 屏幕顶点
	//GLuint VAO;
	//GLuint VBO;

	VertexData planeData;

	bool isOpen;				// 是否开启屏幕渲染

	bool isMultiSampled;		// 是否开启多采样

	SCREEN_RENDER_TYPE type;

	// 核处理
	mat3 kernel;		// 一般3x3就够了
	float texOffset;
public:
	ScreenRender()
	{
		kernel = mat3(1);
		texOffset = 1 / 300.f;
		isOpen = false;
		type = SCREEN_RENDER_TYPE::NONE;
		isMultiSampled = false;
	}

	// 默认帧缓冲初始化（纹理作为附件， 带有深度缓冲和模板缓冲）
	void InitDefaultFrameBuffer();

	void SetScreenType(SCREEN_RENDER_TYPE _type)
	{
		type = _type;
	}

	void SetKernelParams(mat3 _kernel = mat3(0), float _offset = 1 / 300.f)
	{
		kernel = _kernel;
		texOffset = _offset;
	}

	void SetSharpenKernel()
	{
		kernel = mat3(-1, -1, -1, -1, 9, -1, -1, -1, -1);
		texOffset = 1 / 300.f;
	}

	void SetBlurKernel()
	{
		kernel = mat3(1, 2, 1, 2, 4, 2, 1, 2, 1) / 16.f;
		texOffset = 1 / 300.f;
	}

	// 将场景渲染到帧缓冲中
	template<typename F>
	void RenderToFBO(F const& renderFun)
	{
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "need complete framebuffer" << std::endl;
			return;
		}

		if (isMultiSampled)
			glBindFramebuffer(GL_FRAMEBUFFER, multiSampledBuffer);
		else
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderFun();
		if (isMultiSampled)
		{
			glBindFramebuffer(GL_READ_FRAMEBUFFER, multiSampledBuffer);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
			glBlitFramebuffer(0, 0, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	// 将纹理渲染到屏幕plane上
	void Render()
	{
		// 可以根据type进行不同的渲染
		decltype(auto) tool = ShaderDataTool::GetInstance();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);		// 此处关闭深度测试，因为不进行矩阵乘法，深度值是写死的0

		auto shader = ShaderManager::GetInstance().GetShader("SF_ScreenRender");
		glUseProgram(shader->p);
		glBindVertexArray(planeData.VAO);
		tool.SetUniform("screenType", (int)type, shader);
		tool.SetTexture(texColorAttach->id, 0, GL_TEXTURE0, "screenTexture", shader);
		if (type == SCREEN_RENDER_TYPE::KERNEL)
		{
			tool.SetUniform("kernel", kernel, shader);
			tool.SetUniform("texOffset", texOffset, shader);
		}

		glDrawArrays(GL_TRIANGLES, 0, planeData.totalVertex);
		glBindVertexArray(0);
		glUseProgram(0);
	}

private:
	void CreatePlane();
	// 创建普通纹理
	GLuint CreateTexAttach();
	// 创建采样纹理
	void CreateMultiSampledTexAttach(GLuint& tex);
	// 创建采样缓冲
	void CreateMultiSampledFBO();
	// 创建普通缓冲
	void CreateFBO();
	// 初始化默认的屏幕顶点缓冲
	void InitDefaultVertexBuffer()
	{
		CreatePlane();
		ShaderDataTool::GetInstance().InitVertexBuffer(planeData, planeData.VAO, planeData.VBO);
	}
};