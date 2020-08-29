#pragma once
#include<glm.hpp>
#include<string>
#include<memory>
using namespace std;
using namespace glm;

const string COMPONENT_CAMERA = "Camera";
const string COMPONENT_TRANSFORM = "Transform";
const string COMPONENT_MESH = "Mesh";
const string COMPONENT_MESHRENDER = "MeshRenderer";
const string COMPONENT_MESHREFERENCE = "MeshReference";
const string COMPONENT_LIGHT = "Light";

class Object;

class Component : public std::enable_shared_from_this<Component>
{
public:
	//COMPONENTTYPE type;
	string type;
	bool isActive = true;
	weak_ptr<Object> object;
	//Object* object;
public:
	// ÿ�������ÿһ֡����Ҫ���еĸ���
	virtual void Update(float dt) = 0;

	~Component()
	{
		//object = nullptr;
	}

	// ͨ������object������active�ж��Ƿ񷢻�����Ĺ���
	bool isUseable();

	shared_ptr<Object> GetAttachObj()
	{
		if (!object.expired())
			return object.lock();
		return nullptr;
	}
};