#include "ShaderDataTool.h"

void ShaderDataTool::InitTextureWithFile(GLuint& texID, string texPath)
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

void ShaderDataTool::SetTexture(GLuint& texId, int num, GLenum texNum, string samplerName, weak_ptr<ShaderProgram> p)
{
	GLuint texLocation;
	glActiveTexture(texNum);							//��������Ԫ(����λ��)��
	glBindTexture(GL_TEXTURE_2D, texId);				//���������󶨵���ǰ���������Ԫ��
	//������ָ����������Ӧ�ĸ�����Ԫ
	texLocation = glGetUniformLocation(p.lock()->p, samplerName.c_str());	//��ȡ��������location
	glUniform1i(texLocation, num);									//ָ����������Ӧ��ǰ�󶨵�����Ԫ0
}

void ShaderDataTool::SetUniform(string&& valueName, mat4x4 value, weak_ptr<ShaderProgram> p)
{
	GLuint location;
	location = glGetUniformLocation(p.lock()->p, valueName.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(value));
}

void ShaderDataTool::SetUniform(string&& valueName, vec4 value, weak_ptr<ShaderProgram> p)
{
	GLuint location;
	location = glGetUniformLocation(p.lock()->p, valueName.c_str());
	glUniform4fv(location, 1, value_ptr(value));
}

void ShaderDataTool::SetUniform(string&& valueName, vec3 value, weak_ptr<ShaderProgram> p)
{
	GLuint location;
	location = glGetUniformLocation(p.lock()->p, valueName.c_str());
	glUniform3fv(location, 1, value_ptr(value));
}

void ShaderDataTool::SetUniform(string&& valueName, float value, weak_ptr<ShaderProgram> p)
{
	GLuint location;
	location = glGetUniformLocation(p.lock()->p, valueName.c_str());
	glUniform1f(location, value);
}

void ShaderDataTool::SetUniform(string&& valueName, int value, weak_ptr<ShaderProgram> p)
{
	GLuint location;
	location = glGetUniformLocation(p.lock()->p, valueName.c_str());
	glUniform1i(location, value);
}


