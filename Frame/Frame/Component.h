#pragma once

enum class COMPONENTTYPE
{
	COMPONENT_CAMERA,
	COMPONENT_LIGHT,
	COMPONENT_RENDERER
};

class Component
{
public:
	COMPONENTTYPE type;
public:
	virtual void ExcuteResponsibility() = 0;
};

class Camera : public Component
{
public:

public:
	Camera()
	{
		
	}
};

class Light :public Component
{
public:

public:

};

class Renderer :public Component
{

};