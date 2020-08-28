#pragma once
//#include<GL/glew.h>
#include<glad/glad.h>
#include<iostream>
class ShaderProgram
{
public:
	GLuint p;
	GLuint v;
	GLuint f;
public:
	void SetShader(const char*VSFile, const char*FSFile);
private:
	void printShaderInfoLog(GLuint obj);			//shader���������Ϣ���
	void printProgramInfoLog(GLuint obj);			//shader�������Ӵ�����Ϣ���
	char *textFileRead(const char *fn);
};