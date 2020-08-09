#pragma once
#include<glad/glad.h>
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include<SOIL.h>
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
	// 从文件初始化图片到id中
	template<typename T>
	void InitTextureWithFile(GLuint& texID, T&& texPath);
	//传texture到shader中
	void SetTexture(GLuint& texId, int num, GLenum texNum, string samplerName, ShaderProgram& p);
	//根据不同类型的值用重载的方式传入shader中
	void SetUniform(string&& valueName, mat4x4 value, ShaderProgram& p);
	void SetUniform(string&& valueName, vec4 value, ShaderProgram& p);
	void SetUniform(string&& valueName, vec3 value, ShaderProgram& p);
	void SetUniform(string&& valueName, float value, ShaderProgram& p);
};

template<typename T>
inline void ShaderDataTool::InitTextureWithFile(GLuint& texID, T&& texPath)
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
	unsigned char* pResult = SOIL_load_image(texPath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pResult);
	//生成一个mipmap
	glGenerateMipmap(GL_TEXTURE_2D);
	//解除绑定并释放
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(pResult);
}
