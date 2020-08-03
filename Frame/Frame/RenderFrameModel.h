#pragma once
#include<iostream>
#include<glm.hpp>
using namespace glm;

#include"DataModel.h"
#include"Scene.h"

class RenderFrameModel : public DataModel
{
protected:
	RenderFrameModel() {};
public:
	static RenderFrameModel& GetInstance()
	{
		static RenderFrameModel instance;
		return instance;
	}
	RenderFrameModel(RenderFrameModel&) = delete;
public:
	weak_ptr<MyScene> currentScene;


public:
	void SetCurrentScene(shared_ptr<MyScene> scene) { currentScene = scene; }
public:
	shared_ptr<MyScene> GetCurrentScene()
	{
		if (!currentScene.expired())
		{
			return currentScene.lock();
		}
		return nullptr;
	}
};