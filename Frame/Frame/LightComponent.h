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

	void SetLightType(LIGHT_TYPE type)
	{
		switch (type)
		{
		case LIGHT_TYPE::DIRECT_LIGHT:
			light = make_shared<DirLight>();
			break;
		case LIGHT_TYPE::POINT_LIGHT:
			light = make_shared<PointLight>();
			break;
		default:
			break;
		}
	}

	void Update(float dt) override
	{

	}
};