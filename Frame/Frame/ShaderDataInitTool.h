#pragma once
#include<GL/glew.h>
#include<vector>
#include<string>
#include<SOIL.h>
#include<iostream>
#include"VertexData.h"
using namespace std;

class ShaderDataInitTool
{
private:
	static ShaderDataInitTool* instance;
	ShaderDataInitTool()
	{
	}

	// ������Ķ�����Ϣ�Ļ�������ɢ��pos normal tex����������
	//void VertexDataUnpack(vector<float>& vertexData, vector<float>& vertexPos, vector<float>& vertexNormal, vector<float>& vertexTex);
public:
	static ShaderDataInitTool* GetShaderDataInitTool()
	{
		if (instance == NULL)
		{
			instance = new ShaderDataInitTool();
		}
		return instance;
	}
	void InitVertexBuffer(GLuint& VAO, GLuint& VBO, VertexData& vertexData);
	//void UpdateVertexBuffer(GLuint& VAO, GLuint& VBO, vector<float>& vertexData, bool providedNormal, bool providedTex);

	template<typename T>
	void InitTextureWithFile(GLuint& texID, T&& texPath);


	//void InitBufferVC(GLuint& VAO, GLuint& VBO, vector<float>& vertexData, GLenum usage = GL_STATIC_DRAW);
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
	unsigned char* pResult = SOIL_load_image(texPath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pResult);
	//����һ��mipmap
	glGenerateMipmap(GL_TEXTURE_2D);
	//����󶨲��ͷ�
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(pResult);
}
