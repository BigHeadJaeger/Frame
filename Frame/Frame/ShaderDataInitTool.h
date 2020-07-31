#pragma once
//#include<GL/glew.h>
#include<glad/glad.h>
#include<vector>
#include<string>
#include<SOIL.h>
#include<iostream>
#include"VertexData.h"
using namespace std;

class ShaderDataInitTool
{
private:
	ShaderDataInitTool() {}
public:
	//ShaderDataInitTool(ShaderDataInitTool&) = delete;
	static ShaderDataInitTool& GetShaderDataInitTool()
	{
		static ShaderDataInitTool instance;
		return instance;
	}
	void InitVertexBuffer(GLuint& VAO, GLuint& VBO, VertexData& vertexData);
	template<typename T>
	void InitTextureWithFile(GLuint& texID, T&& texPath);
	//ShaderDataInitTool(ShaderDataInitTool&) = delete;
};

template<typename T>
inline void ShaderDataInitTool::InitTextureWithFile(GLuint& texID, T&& texPath)
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
