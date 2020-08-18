#pragma once
#include<glm.hpp>
#include<string>
using namespace std;
using namespace glm;

const string COMPONENT_CAMERA = "Camera";
const string COMPONENT_TRANSFORM = "Transform";
const string COMPONENT_MESH = "Mesh";
const string COMPONENT_MESHRENDER = "MeshRenderer";
const string COMPONENT_MESHREFERENCE = "MeshReference";
const string COMPONENT_LIGHT = "Light";

class Object;

class Component
{
public:
	//COMPONENTTYPE type;
	string type;
	bool isActive = true;
	Object* object;
	//void* object;
public:
	// 每个组件在每一帧中需要进行的更新
	virtual void Update(float dt) = 0;

	~Component()
	{
		object = nullptr;
	}

	// 通过依附object和自身active判断是否发挥组件的功能
	bool isUseable();
};