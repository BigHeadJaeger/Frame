#pragma once
#include<glm.hpp>
using namespace glm;


enum class COMPONENTTYPE
{
	COMPONENT_CAMERA,
	COMPONENT_LIGHT,
	COMPONENT_RENDERER,
	COMPONENT_TRANSFORM
};

class Component
{
public:
	COMPONENTTYPE type;
public:
	// ÿ�������ÿһ֡����Ҫ���еĸ���
	virtual void Update() = 0;
};

class Light :public Component
{
public:

public:

};

class Renderer :public Component
{

};