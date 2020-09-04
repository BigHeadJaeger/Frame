// 处理屏幕渲染
#pragma once
#include<iostream>
#include<string>
#include<glad/glad.h>
#include<functional>
#include"Const.h"
#include"ShaderDataTool.h"
#include"ShaderManager.h"

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
	GLuint texColorBuffer;
	GLuint DSRenderBuffer;		// 深度和模板的RBO

	// 屏幕顶点
	//GLuint VAO;
	//GLuint VBO;

	VertexData planeData;

	bool isOpen;				// 是否开启屏幕渲染

	SCREEN_RENDER_TYPE type;

	// 核处理
	mat3 kernel;		// 一般3x3就够了
	float texOffset;
public:
	ScreenRender()
	{
		kernel = mat3(1);
		//kernel = mat3(1, 2, 3, 4, 5, 6, 7, 8, 9);
		//mat3x4 m1 = mat3x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
		//auto test = m1.length();
		//auto test2 = m1[0].length();
		//for (size_t i = 0; i < kernel.length(); i++)
		//{

		//}
		texOffset = 1 / 300.f;
		isOpen = false;
		type = SCREEN_RENDER_TYPE::NONE;
	}

	// 默认帧缓冲初始化（纹理作为附件， 带有深度缓冲和模板缓冲）
	void InitDefaultFrameBuffer()
	{
		glDeleteFramebuffers(1, &FBO);		// 先清除已有的缓冲
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		glDeleteTextures(1, &texColorBuffer);
		glGenTextures(1, &texColorBuffer);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texColorBuffer, 0);

		glDeleteRenderbuffers(1, &DSRenderBuffer);
		glGenRenderbuffers(1, &DSRenderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, DSRenderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, DSRenderBuffer);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "framebuffer not complete" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);		// 复位默认帧缓冲

		// 初始化顶点
		InitDefaultVertexBuffer();
	}

	// 初始化默认的屏幕顶点缓冲
	void InitDefaultVertexBuffer()
	{
		CreatePlane();
		ShaderDataTool::GetInstance().InitVertexBuffer(planeData, planeData.VAO, planeData.VBO);
	}

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

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderFun();
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
		tool.SetTexture(texColorBuffer, 0, GL_TEXTURE0, "screenTexture", shader);
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
	void CreatePlane()
	{
		planeData.Clear();
		planeData.totalVertex = 6;
		planeData.setState(STATE_TYPE_POSITION, true);
		planeData.setLocation(STATE_TYPE_POSITION, 0);
		planeData.position.push_back(vec3(-1.f, 1.f, 0.f));
		planeData.position.push_back(vec3(-1.f, -1.f, 0.f));
		planeData.position.push_back(vec3(1.f, -1.f, 0.f));
		planeData.position.push_back(vec3(-1.f, 1.f, 0.f));
		planeData.position.push_back(vec3(1.f, -1.f, 0.f));
		planeData.position.push_back(vec3(1.f, 1.f, 0.f));

		planeData.setState(STATE_TYPE_TEXCOORD, true);
		planeData.setLocation(STATE_TYPE_TEXCOORD, 1);
		planeData.texcoord.push_back(vec2(0.f, 1.f));
		planeData.texcoord.push_back(vec2(0.f, 0.f));
		planeData.texcoord.push_back(vec2(1.f, 0.f));
		planeData.texcoord.push_back(vec2(0.f, 1.f));
		planeData.texcoord.push_back(vec2(1.f, 0.f));
		planeData.texcoord.push_back(vec2(1.f, 1.f));
	}
};