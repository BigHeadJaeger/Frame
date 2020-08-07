#pragma once
#include<glad/glad.h>
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
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

	//��texture��shader��
	void SetTexture(GLuint& texId, int num, GLenum texNum, string samplerName, ShaderProgram& p);
	//���ݲ�ͬ���͵�ֵ�����صķ�ʽ����shader��
	void SetUniform(string&& valueName, mat4x4 value, ShaderProgram& p);
	void SetUniform(string&& valueName, vec4 value, ShaderProgram& p);
	void SetUniform(string&& valueName, vec3 value, ShaderProgram& p);
	void SetUniform(string&& valueName, float value, ShaderProgram& p);
};