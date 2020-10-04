#include "ScreenRender.h"

void ScreenRender::InitDefaultFrameBuffer()
{
	if (isMultiSampled)
	{
		// 创建多重采样的FBO
		CreateMultiSampledFBO();
		// 创建普通的FBO，用于多重帧缓冲结果的分离目标
		CreateFBO();
	}
	else
		CreateFBO();
	// 初始化顶点
	InitDefaultVertexBuffer();
}

void ScreenRender::CreatePlane()
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

GLuint ScreenRender::CreateTexAttach()
{
	texColorAttach.reset();
	texColorAttach = make_shared<Texture2D>();
	texColorAttach->Create(WIDTH, HEIGHT);
	return texColorAttach->id;
}

void ScreenRender::CreateMultiSampledTexAttach(GLuint& tex)
{
	glDeleteTextures(1, &tex);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, tex);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, WIDTH, HEIGHT, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
}

void ScreenRender::CreateMultiSampledFBO()
{
	glDeleteFramebuffers(1, &multiSampledBuffer);		// 先清除已有的缓冲
	glGenFramebuffers(1, &multiSampledBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, multiSampledBuffer);

	CreateMultiSampledTexAttach(multiSampledColorBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, multiSampledColorBuffer, 0);

	glDeleteRenderbuffers(1, &multiSampledRenderBuffer);
	glGenRenderbuffers(1, &multiSampledRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, multiSampledRenderBuffer);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, multiSampledRenderBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "framebuffer not complete" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);		// 复位默认帧缓冲
}

void ScreenRender::CreateFBO()
{
	glDeleteFramebuffers(1, &FBO);		// 先清除已有的缓冲
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	auto textureID = CreateTexAttach();
	
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureID, 0);

	glDeleteRenderbuffers(1, &DSRenderBuffer);
	glGenRenderbuffers(1, &DSRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, DSRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, DSRenderBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "framebuffer not complete" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);		// 复位默认帧缓冲
}
