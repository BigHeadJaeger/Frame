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
	//根据不同类型的值用重载的方式传入shader中
	void SetUniform(string&& valueName, mat4x4 value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, mat3x3 value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, vec4 value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, vec3 value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, float value, weak_ptr<ShaderProgram> p);
	void SetUniform(string&& valueName, int value, weak_ptr<ShaderProgram> p);

	// 通用的将vertex data传入到顶点缓冲中
	void InitVertexBuffer(VertexData& vertexData, GLuint& VAO, GLuint& VBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		//创建顶点buffer
		glDeleteBuffers(1, &VBO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);					//先绑定，在用VAO传值时，就传送的是当前绑定的buffer

		GLsizeiptr sumSize = vertexData.position.size() * sizeof(vec3) + vertexData.normal.size() * sizeof(vec3) + vertexData.texcoord.size() * sizeof(vec2) + vertexData.color.size() * sizeof(vec4);
		//开辟空间
		glBufferData(GL_ARRAY_BUFFER, sumSize, NULL, GL_STATIC_DRAW);

		GLintptr offset = 0;

		for (auto state_it = vertexData.propertyState.begin(); state_it != vertexData.propertyState.end(); state_it++)
		{
			if ((*state_it).second.isEnable)
			{
				GLintptr size = 0;
				switch ((*state_it).first)
				{
				case STATE_TYPE_POSITION:
					size = vertexData.position.size() * sizeof(vec3);
					glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertexData.position[0]);

					glEnableVertexAttribArray((*state_it).second.location);
					glVertexAttribPointer((*state_it).second.location, 3, GL_FLOAT, GL_FALSE, 0, (void*)offset);

					offset += size;
					break;
				case STATE_TYPE_NORMAL:
					size = vertexData.normal.size() * sizeof(vec3);
					glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertexData.normal[0]);

					glEnableVertexAttribArray((*state_it).second.location);
					glVertexAttribPointer((*state_it).second.location, 3, GL_FLOAT, GL_FALSE, 0, (void*)offset);

					offset += size;
					break;
				case STATE_TYPE_TEXCOORD:
					size = vertexData.texcoord.size() * sizeof(vec2);
					glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertexData.texcoord[0]);

					glEnableVertexAttribArray((*state_it).second.location);
					glVertexAttribPointer((*state_it).second.location, 2, GL_FLOAT, GL_FALSE, 0, (void*)offset);

					offset += size;
					break;
				case STATE_TYPE_COLOR:
					size = vertexData.color.size() * sizeof(vec4);
					glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertexData.color[0]);

					glEnableVertexAttribArray((*state_it).second.location);
					glVertexAttribPointer((*state_it).second.location, 4, GL_FLOAT, GL_FALSE, 0, (void*)offset);

					offset += size;
					break;
				default:
					break;
				}
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
};
