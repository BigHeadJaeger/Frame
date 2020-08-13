#pragma once
#include<glm.hpp>
#include<string>
using namespace glm;

//
//enum class COMPONENTTYPE
//{
//	COMPONENT_CAMERA,
//	COMPONENT_LIGHT,
//	COMPONENT_RENDERER,
//	COMPONENT_TRANSFORM
//};
const string COMPONENT_CAMERA = "Camera";
const string COMPONENT_TRANSFORM = "Transform";
const string COMPONENT_MESH = "Mesh";
const string COMPONENT_MESHRENDER = "MeshRenderer";

class Component
{
public:
	//COMPONENTTYPE type;
	string type;

	shared_ptr<void> object;
	//void* object;
public:
	Component(shared_ptr<void> atatch)
	{
		object = atatch;
	}
	// 每个组件在每一帧中需要进行的更新
	virtual void Update() = 0;

	//virtual void TransferData(ShaderProgram& shaderProgram) = 0;
};

class Light :public Component
{
public:

public:

};

class Renderer :public Component
{

};