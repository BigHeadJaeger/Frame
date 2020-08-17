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

class Object;

class Component
{
public:
	//COMPONENTTYPE type;
	string type;

	Object* object;
	//void* object;
public:
	// 每个组件在每一帧中需要进行的更新
	virtual void Update(float dt) = 0;

	~Component()
	{
		object = nullptr;
	}
};