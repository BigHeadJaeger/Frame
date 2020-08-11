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
	// 每个组件在每一帧中需要进行的更新
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