#pragma once
#include<glm.hpp>
#include"Object.h"
using namespace glm;

// ÿ������Ҳ��һ��object�����й�����Ҫ������һ�������д���
class Light
{
public:
	vec3 lightPos;
	vec3 lightColor;
};

// ����⣬ƽ�й�
class DirLight:public Light
{
public:
	vec3 lightDir;
};


class PointLight :public Light
{
	float radius;
	float attenuation;
};
