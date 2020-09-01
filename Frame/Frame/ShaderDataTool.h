#pragma once
#include<glad/glad.h>
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include<SOIL.h>
#include<string>
using namespace glm;
using namespace std;

#include"Program.h"

class ShaderDataTool
{
private:
	ShaderDataTool() {};
public:
	static ShaderDataTool& GetInstance()
	{
		static ShaderDataTool instance;
		return instance;
	}
	ShaderDataTool(ShaderDataTool&) = delete;
	// ���ļ���ʼ��ͼƬ��id��
	void InitTextureWithFile(GLuint& texID, string texPath);
	//��texture��shader��
	void SetTexture(GLuint& texId, int num, GLenum texNum, string samplerName, weak_ptr<ShaderProgram> p);
	//���ݲ�ͬ���͵�ֵ�����صķ�ʽ����shader��
	void SetUniform(string&& valueName, mat4x4 value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, vec4 value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, vec3 value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, float value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, int value, weak_ptr<ShaderProgram> p);
};
