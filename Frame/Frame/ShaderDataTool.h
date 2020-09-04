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
#include"VertexData.h"
#include"Texture.h"

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
	// 从文件初始化图片到id中
	void InitTextureWithFile(GLuint& texID, string texPath);
	//传texture到shader中
	void SetTexture(GLuint& texId, int num, GLenum texNum, string samplerName, weak_ptr<ShaderProgram> p);
	//void SetTexture(shared_ptr<Texture> texture, int num, GLenum texNum, string samplerName, weak_ptr<ShaderProgram> p);
	//根据不同类型的值用重载的方式传入shader中
	void SetUniform(string&& valueName, mat4x4 value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, mat3x3 value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, vec4 value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, vec3 value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, float value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, int value, weak_ptr<ShaderProgram> p);

	// 通用的将vertex data传入到顶点缓冲中
	void InitVertexBuffer(VertexData& vertexData, GLuint& VAO, GLuint& VBO);
};
