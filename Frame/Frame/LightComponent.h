#pragma once
#include<memory>
#include"Light.h"
#include"Component.h"

class LightComponent : public Component
{
public:
	shared_ptr<Light> light;
	LightComponent()
	{
		light = make_shared<DirLight>();
	}

	void Update(float dt) override
	{

	}
};