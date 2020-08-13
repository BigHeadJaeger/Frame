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
public:
	// ÿ�������ÿһ֡����Ҫ���еĸ���
	virtual void Update() = 0;

	virtual void TransferData(ShaderProgram& shaderProgram) = 0;
};

class Light :public Component
{
public:

public:

};

class Renderer :public Component
{

};