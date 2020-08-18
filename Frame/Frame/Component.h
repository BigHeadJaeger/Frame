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
	// ÿ�������ÿһ֡����Ҫ���еĸ���
	virtual void Update(float dt) = 0;

	~Component()
	{
		object = nullptr;
	}

	// ͨ������object������active�ж��Ƿ񷢻�����Ĺ���
	bool isUseable();
};