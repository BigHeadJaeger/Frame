#include "ShaderDataInitTool.h"

ShaderDataInitTool* ShaderDataInitTool::instance = NULL;

void ShaderDataInitTool::InitVertexBuffer(GLuint& VAO, GLuint& VBO, VertexData& vertexData)
{
	glDeleteVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//vector<float> vertexPos;
	//vector<float> vertexNormal;
	//vector<float> vertexTex;
	//vector<float> vertexColor;
	//bool colorExist;
	//if (vertexColor.size() > 0)
	//	colorExist = true;
	//else
	//	colorExist = false;

	//bool tempArray[] = { vertexData.isPosition, vertexData.isNormal, vertexData.isTexcoord, vertexData.isColor };
	//vector<bool> propertyState(tempArray, tempArray + 4);


	//for (int i = 0; i < vertexData.totalVertex; i++)
	//{
	//	if (vertexData.GetPosState())
	//	{
	//		vertexPos.push_back(vertexData.position[i].x);
	//		vertexPos.push_back(vertexData.position[i].y);
	//		vertexPos.push_back(vertexData.position[i].z);
	//	}

	//	if (vertexData.GetNorState())
	//	{
	//		vertexNormal.push_back(vertexData.normal[i].x);
	//		vertexNormal.push_back(vertexData.normal[i].y);
	//		vertexNormal.push_back(vertexData.normal[i].z);
	//	}

	//	if (vertexData.GetTexState())
	//	{
	//		vertexTex.push_back(vertexData.texcoord[i].x);
	//		vertexTex.push_back(vertexData.texcoord[i].y);
	//	}

	//	if (vertexData.GetColorState())
	//	{
	//		vertexColor.push_back(vertexData.color[i].x);
	//		vertexColor.push_back(vertexData.color[i].y);
	//		vertexColor.push_back(vertexData.color[i].z);
	//		vertexColor.push_back(vertexData.color[i].w);
	//	}
	//	//else
	//	//{
	//	//	vertexColor.push_back(1);
	//	//	vertexColor.push_back(1);
	//	//	vertexColor.push_back(1);
	//	//	vertexColor.push_back(1);
	//	//}

	//}
	//for (int i = 0; i < vertexData.size(); i = i + 8)
	//{
	//	vertexPos.push_back(vertexData[i]);
	//	vertexPos.push_back(vertexData[i + 1]);
	//	vertexPos.push_back(vertexData[i + 2]);
	//	vertexNormal.push_back(vertexData[i + 3]);
	//	vertexNormal.push_back(vertexData[i + 4]);
	//	vertexNormal.push_back(vertexData[i + 5]);
	//	vertexTex.push_back(vertexData[i + 6]);
	//	vertexTex.push_back(vertexData[i + 7]);
	//	//vertexColor.push_back(vertexData[i + 8]);
	//	//vertexColor.push_back(vertexData[i + 9]);
	//	//vertexColor.push_back(vertexData[i + 10]);
	//	//vertexColor.push_back(vertexData[i + 11]);
	//}

	//��������buffer
	glDeleteBuffers(1, &VBO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);					//�Ȱ󶨣�����VAO��ֵʱ���ʹ��͵��ǵ�ǰ�󶨵�buffer

	//GLsizeiptr sumSize = vertexData.size() * sizeof(float);
	//GLsizeiptr sumSize = (vertexPos.size() + vertexNormal.size() + vertexTex.size() + vertexColor.size()) * sizeof(float);
	//GLsizeiptr sumSize = (vertexData.position.size() + vertexData.normal.size() + vertexData.texcoord.size() + vertexData.color.size()) * sizeof(vec3);
	GLsizeiptr sumSize = vertexData.position.size() * sizeof(vec3) + vertexData.normal.size() * sizeof(vec3) + vertexData.texcoord.size() * sizeof(vec2) + vertexData.color.size() * sizeof(vec4);
	//���ٿռ�
	glBufferData(GL_ARRAY_BUFFER, sumSize, NULL, GL_STATIC_DRAW);

	GLintptr offset = 0;

	map<StateType, StateInfo>::iterator state_it;
	for (state_it = vertexData.propertyState.begin(); state_it != vertexData.propertyState.end(); state_it++)
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
				glVertexAttribPointer((*state_it).second.location, 3, GL_FLOAT, GL_FALSE, 1 * sizeof(vec3), (void*)offset);

				offset += size;
				break;
			case STATE_TYPE_NORMAL:
				size = vertexData.normal.size() * sizeof(vec3);
				glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertexData.normal[0]);

				glEnableVertexAttribArray((*state_it).second.location);
				glVertexAttribPointer((*state_it).second.location, 3, GL_FLOAT, GL_FALSE, 1 * sizeof(vec3), (void*)offset);

				offset += size;
				break;
			case STATE_TYPE_TEXCOORD:
				size = vertexData.texcoord.size() * sizeof(vec2);
				glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertexData.texcoord[0]);

				glEnableVertexAttribArray((*state_it).second.location);
				glVertexAttribPointer((*state_it).second.location, 2, GL_FLOAT, GL_FALSE, 1 * sizeof(vec2), (void*)offset);

				offset += size;
				break;
			case STATE_TYPE_COLOR:
				size = vertexData.color.size() * sizeof(vec4);
				glBufferSubData(GL_ARRAY_BUFFER, offset, size, &vertexData.color[0]);

				glEnableVertexAttribArray((*state_it).second.location);
				glVertexAttribPointer((*state_it).second.location, 4, GL_FLOAT, GL_FALSE, 1 * sizeof(vec4), (void*)offset);

				offset += size;
				break;
			default:
				break;
			}
		}
	}


	//��ʼ������
	//glBufferSubData(GL_ARRAY_BUFFER, offset, vertexPos.size() * sizeof(float), &vertexPos[0]);
			//vector<float> test;
			//test.resize(vertexPos.size());
			//glGetBufferSubData(GL_ARRAY_BUFFER, offset, vertexPos.size() * sizeof(float), &test[0]);
	//offset += vertexPos.size() * sizeof(float);
	//glBufferSubData(GL_ARRAY_BUFFER, offset, vertexNormal.size() * sizeof(float), &vertexNormal[0]);
	//offset += vertexNormal.size() * sizeof(float);
	//glBufferSubData(GL_ARRAY_BUFFER, offset, vertexTex.size() * sizeof(float), &vertexTex[0]);
	//offset += vertexTex.size() * sizeof(float);
	//glBufferSubData(GL_ARRAY_BUFFER, offset, vertexColor.size() * sizeof(float), &vertexColor[0]);
	//offset += vertexColor.size() * sizeof(float);

			//void* testData = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
			//vector<float>* a = (vector<float>*)testData;
			//float* a = (float*)testData;


	//GLint index = 0;
	//GLsizeiptr size = 0;
	////����Ҫ��glVertexAttribPointer���¶�������ָ��
	//glEnableVertexAttribArray(index);
	//glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)size);
	//index++;
	//size += vertexPos.size() * sizeof(float);
	//glEnableVertexAttribArray(index);
	//glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)size);
	//index++;
	//size += vertexNormal.size() * sizeof(float);
	//glEnableVertexAttribArray(index);
	//glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)size);
	//index++;
	//size += vertexTex.size() * sizeof(float);
	//glEnableVertexAttribArray(index);
	//glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)size);
	//index++;
	//size += vertexColor.size() * sizeof(float);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

//void ShaderDataInitTool::InitVertexBuffer(GLuint& VAO, GLuint& VBO, VertexData& vertexData)
//{
//	glDeleteVertexArrays(1, &VAO);
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//	//vector<float> vertexPos;
//	//vector<float> vertexNormal;
//	//vector<float> vertexTex;
//	//vector<float> vertexColor;
//	//for (int i = 0; i < vertexData.size(); i = i + 8)
//	//{
//	//	vertexPos.push_back(vertexData[i]);
//	//	vertexPos.push_back(vertexData[i + 1]);
//	//	vertexPos.push_back(vertexData[i + 2]);
//	//	vertexNormal.push_back(vertexData[i + 3]);
//	//	vertexNormal.push_back(vertexData[i + 4]);
//	//	vertexNormal.push_back(vertexData[i + 5]);
//	//	vertexTex.push_back(vertexData[i + 6]);
//	//	vertexTex.push_back(vertexData[i + 7]);
//	//	//vertexColor.push_back(vertexData[i + 8]);
//	//	//vertexColor.push_back(vertexData[i + 9]);
//	//	//vertexColor.push_back(vertexData[i + 10]);
//	//	//vertexColor.push_back(vertexData[i + 11]);
//	//}
//
//	//��������buffer
//	glDeleteBuffers(1, &VBO);
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);					//�Ȱ󶨣�����VAO��ֵʱ���ʹ��͵��ǵ�ǰ�󶨵�buffer
//
//	//GLsizeiptr sumSize = vertexData.size() * sizeof(float);
//	//vertexData
//	GLsizeiptr posSize = vertexData.position.size() * sizeof(vec3);
//	GLsizeiptr norSize = vertexData.normal.size() * sizeof(vec3);
//	GLsizeiptr texSize = vertexData.texcoord.size() * sizeof(vec2);
//	GLsizeiptr colorSize = vertexData.color.size() * sizeof(vec4);
//
//
//	GLsizeiptr sumSize = posSize + norSize + texSize + colorSize;
//	
//	//���ٿռ�
//	glBufferData(GL_ARRAY_BUFFER, sumSize, NULL, GL_STATIC_DRAW);
//
//	GLintptr offset = 0;
//	//��ʼ������
//	glBufferSubData(GL_ARRAY_BUFFER, offset, posSize, &vertexData.position[0]);
//	//vector<float> test;
//	//test.resize(vertexPos.size());
//	//glGetBufferSubData(GL_ARRAY_BUFFER, offset, vertexPos.size() * sizeof(float), &test[0]);
//	offset += posSize;
//	glBufferSubData(GL_ARRAY_BUFFER, offset, norSize, &vertexData.normal[0]);
//	offset += norSize;
//	glBufferSubData(GL_ARRAY_BUFFER, offset, texSize, &vertexData.texcoord[0]);
//	offset += texSize;
//	glBufferSubData(GL_ARRAY_BUFFER, offset, colorSize, &vertexData.color[0]);
//	offset += colorSize;
//
//	//void* testData = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
//	//vector<float>* a = (vector<float>*)testData;
//	//float* a = (float*)testData;
//
//
//	GLint index = 0;
//	GLsizeiptr size = 0;
//	//����Ҫ��glVertexAttribPointer���¶�������ָ��
//	glEnableVertexAttribArray(index);
//	glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(vec3), (void*)size);
//	index++;
//	size += posSize;
//	glEnableVertexAttribArray(index);
//	glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(vec3), (void*)size);
//	index++;
//	size += norSize;
//	glEnableVertexAttribArray(index);
//	glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(vec2), (void*)size);
//	index++;
//	size += texSize;
//	glEnableVertexAttribArray(index);
//	glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(vec4), (void*)size);
//	index++;
//	size += colorSize;
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//}


//void ShaderDataInitTool::InitTextureWithFile(GLuint& texID, string texPath)
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
