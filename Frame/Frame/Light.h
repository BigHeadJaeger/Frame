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
class Light
{
public:
	LIGHT_TYPE type;
	vec3 lightColor = vec3(255);

 	virtual void temp() = 0;
};

// 方向光，平行光
class DirLight:public Light
{
public:
	vec3 lightDir;
public:
	DirLight()
	{
		lightDir = normalize(vec3(1, -1, 1));
		type = LIGHT_TYPE::DIRECT_LIGHT;
	}

	template<typename V>
	void SetDir(V&& dir)
	{
		lightDir = normalize(dir);
	}

	void temp()override {}
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
	void temp()override {}
};
