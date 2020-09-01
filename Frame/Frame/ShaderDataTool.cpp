#include "ShaderDataTool.h"

void ShaderDataTool::InitTextureWithFile(GLuint& texID, string texPath)
{
	glGenTextures(1, &texID);					//生成一个纹理ID
	glBindTexture(GL_TEXTURE_2D, texID);		//此时绑定到了默认纹理单元0处，在之后的代码中会指定绑定到具体哪个单元
	//指定贴图方法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//图片文件读取
	int width, height;
	unsigned char* pResult = SOIL_load_image(texPath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pResult);
	//生成一个mipmap
	glGenerateMipmap(GL_TEXTURE_2D);
	//解除绑定并释放
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(pResult);
}

void ShaderDataTool::SetTexture(GLuint& texId, int num, GLenum texNum, string samplerName, weak_ptr<ShaderProgram> p)
{
	GLuint texLocation;
	glActiveTexture(texNum);							//激活纹理单元(纹理位置)。
	glBindTexture(GL_TEXTURE_2D, texId);				//将纹理对象绑定到当前激活的纹理单元处
	//接下来指定采样器对应哪个纹理单元
	texLocation = glGetUniformLocation(p.lock()->p, samplerName.c_str());	//获取采样器的location
	glUniform1i(texLocation, num);									//指定采样器对应当前绑定的纹理单元0
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


