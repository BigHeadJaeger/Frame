#pragma once
#include<glm.hpp>
#include"Component.h"
using namespace glm;

enum class LIGHT_TYPE
{
	DIRECT_LIGHT,
	POINT_LIGHT
};

// 每个光照也是一个object，所有光照需要整合在一个集合中处理
class Light : public Component
{
public:
	LIGHT_TYPE type;
	vec3 lightPos = vec3(0);
	vec3 lightColor = vec3(255);
};

// 方向光，平行光
class DirLight:public Light
{
public:
	vec3 lightDir = vec3(lightPos.x, lightPos.y - 1, lightPos.z);
public:
	DirLight()
	{
		type = LIGHT_TYPE::DIRECT_LIGHT;
	}
};


class PointLight :public Light
{
public:
	float radius = 1.f;
	float attenuation = 0.6f;
public:
	PointLight()
	{
		type = LIGHT_TYPE::POINT_LIGHT;
	}
};
