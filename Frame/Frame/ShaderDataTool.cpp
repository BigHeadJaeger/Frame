#include "ShaderDataTool.h"


//void ShaderDataTool::InitTextureWithFile(GLuint& texID, string texPath)
//{
//	glGenTextures(1, &texID);					//生成一个纹理ID
//	glBindTexture(GL_TEXTURE_2D, texID);		//此时绑定到了默认纹理单元0处，在之后的代码中会指定绑定到具体哪个单元
//	//指定贴图方法
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//图片文件读取
//	int width, height;
//	unsigned char* pResult = SOIL_load_image(texPath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pResult);
//	//生成一个mipmap
//	glGenerateMipmap(GL_TEXTURE_2D);
//	//解除绑定并释放
//	glBindTexture(GL_TEXTURE_2D, 0);
//	SOIL_free_image_data(pResult);
//}

void ShaderDataTool::SetTexture(GLuint& texId, int num, GLenum texNum, string samplerName, weak_ptr<ShaderProgram> p)
{
	GLuint texLocation;
	glActiveTexture(texNum);							//激活纹理单元(纹理位置)。
	glBindTexture(GL_TEXTURE_2D, texId);				//将纹理对象绑定到当前激活的纹理单元处
	//接下来指定采样器对应哪个纹理单元
	texLocation = glGetUniformLocation(p.lock()->p, samplerName.c_str());	//获取采样器的location
	glUniform1i(texLocation, num);									//指定采样器对应当前绑定的纹理单元0
}

void ShaderDataTool::SetTextureCube(GLuint& texId, int num, GLenum texNum, string samplerName, weak_ptr<ShaderProgram> p)
{
	GLuint texLocation;
	glActiveTexture(texNum);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texId);
	texLocation = glGetUniformLocation(p.lock()->p, samplerName.c_str());
	glUniform1i(texLocation, num);
}

//void ShaderDataTool::SetTexture(shared_ptr<Texture> texture, int num, GLenum texNum, string samplerName, weak_ptr<ShaderProgram> p)
//{
//	texture->SettingTexture();
//	GLuint texLocation;
//	glActiveTexture(texNum);							//激活纹理单元(纹理位置)。
//	glBindTexture(GL_TEXTURE_2D, texture->id);				//将纹理对象绑定到当前激活的纹理单元处
//	//接下来指定采样器对应哪个纹理单元
//	texLocation = glGetUniformLocation(p.lock()->p, samplerName.c_str());	//获取采样器的location
//	glUniform1i(texLocation, num);									//指定采样器对应当前绑定的纹理单元0
//}

void ShaderDataTool::SetUniform(string&& valueName, mat4x4 value, weak_ptr<ShaderProgram> p)
{
	GLuint location;
	location = glGetUniformLocation(p.lock()->p, valueName.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(value));
}

void ShaderDataTool::SetUniform(string&& valueName, mat3x3 value, weak_ptr<ShaderProgram> p)
{
	GLuint location;
	location = glGetUniformLocation(p.lock()->p, valueName.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, value_ptr(value));
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

void ShaderDataTool::InitVertexBuffer(VertexData& vertexData, GLuint& VAO, GLuint& VBO)
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


