#pragma once
//#include<GL/glew.h>
#include<glad/glad.h>
#include<iostream>
class ShaderProgram
{
public:
	GLuint p;
	GLuint v;		// 顶点着色器
	GLuint f;		// 片段着色器
	GLuint g;		// 几何着色器
public:
	void SetShader(const char*VSFile, const char*FSFile, const char* GSFile);
private:
	void printShaderInfoLog(GLuint obj);			//shader编译错误信息输出
	void printProgramInfoLog(GLuint obj);			//shader程序链接错误信息输出
	char *textFileRead(const char *fn);
};