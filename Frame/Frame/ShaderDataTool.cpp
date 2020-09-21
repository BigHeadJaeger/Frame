#include "ShaderDataTool.h"


//void ShaderDataTool::InitTextureWithFile(GLuint& texID, string texPath)
//{
//	glGenTextures(1, &texID);					//����һ������ID
//	glBindTexture(GL_TEXTURE_2D, texID);		//��ʱ�󶨵���Ĭ������Ԫ0������֮��Ĵ����л�ָ���󶨵������ĸ���Ԫ
//	//ָ����ͼ����
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//ͼƬ�ļ���ȡ
//	int width, height;
//	unsigned char* pResult = SOIL_load_image(texPath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pResult);
//	//����һ��mipmap
//	glGenerateMipmap(GL_TEXTURE_2D);
//	//����󶨲��ͷ�
//	glBindTexture(GL_TEXTURE_2D, 0);
//	SOIL_free_image_data(pResult);
//}

void ShaderDataTool::SetTexture(GLuint& texId, int num, GLenum texNum, string samplerName, weak_ptr<ShaderProgram> p)
{
	GLuint texLocation;
	glActiveTexture(texNum);							//��������Ԫ(����λ��)��
	glBindTexture(GL_TEXTURE_2D, texId);				//���������󶨵���ǰ���������Ԫ��
	//������ָ����������Ӧ�ĸ�����Ԫ
	texLocation = glGetUniformLocation(p.lock()->p, samplerName.c_str());	//��ȡ��������location
	glUniform1i(texLocation, num);									//ָ����������Ӧ��ǰ�󶨵�����Ԫ0
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
//	glActiveTexture(texNum);							//��������Ԫ(����λ��)��
//	glBindTexture(GL_TEXTURE_2D, texture->id);				//���������󶨵���ǰ���������Ԫ��
//	//������ָ����������Ӧ�ĸ�����Ԫ
//	texLocation = glGetUniformLocation(p.lock()->p, samplerName.c_str());	//��ȡ��������location
//	glUniform1i(texLocation, num);									//ָ����������Ӧ��ǰ�󶨵�����Ԫ0
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

	//��������buffer
	glDeleteBuffers(1, &VBO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);					//�Ȱ󶨣�����VAO��ֵʱ���ʹ��͵��ǵ�ǰ�󶨵�buffer

	GLsizeiptr sumSize = vertexData.position.size() * sizeof(vec3) + vertexData.normal.size() * sizeof(vec3) + vertexData.texcoord.size() * sizeof(vec2) + vertexData.color.size() * sizeof(vec4);
	//���ٿռ�
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


