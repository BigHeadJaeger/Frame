// ������Ļ��Ⱦ
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
	GLuint DSRenderBuffer;				// ��Ⱥ�ģ���RBO

	GLuint multiSampledBuffer;			// ���ز����Ļ���
	GLuint multiSampledColorBuffer;		// ���ز�����������
	GLuint multiSampledRenderBuffer;	// ���ز�������Ⱥ�ģ���RBO


	// ��Ļ����
	//GLuint VAO;
	//GLuint VBO;

	VertexData planeData;

	bool isOpen;				// �Ƿ�����Ļ��Ⱦ

	bool isMultiSampled;		// �Ƿ��������

	SCREEN_RENDER_TYPE type;

	// �˴���
	mat3 kernel;		// һ��3x3�͹���
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

	// Ĭ��֡�����ʼ����������Ϊ������ ������Ȼ����ģ�建�壩
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

	// ��������Ⱦ��֡������
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

	// ��������Ⱦ����Ļplane��
	void Render()
	{
		// ���Ը���type���в�ͬ����Ⱦ
		decltype(auto) tool = ShaderDataTool::GetInstance();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);		// �˴��ر���Ȳ��ԣ���Ϊ�����о���˷������ֵ��д����0

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
	// ������ͨ����
	GLuint CreateTexAttach();
	// ������������
	void CreateMultiSampledTexAttach(GLuint& tex);
	// ������������
	void CreateMultiSampledFBO();
	// ������ͨ����
	void CreateFBO();
	// ��ʼ��Ĭ�ϵ���Ļ���㻺��
	void InitDefaultVertexBuffer()
	{
		CreatePlane();
		ShaderDataTool::GetInstance().InitVertexBuffer(planeData, planeData.VAO, planeData.VBO);
	}
};