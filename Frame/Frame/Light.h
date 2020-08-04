#pragma once
#include<glm.hpp>
#include"Object.h"
using namespace glm;

// 每个光照也是一个object，所有光照需要整合在一个集合中处理
class Light
{
public:
	vec3 lightPos;
	vec3 lightColor;
};

// 方向光，平行光
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
