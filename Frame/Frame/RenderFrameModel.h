#pragma once
#include<iostream>
#include<glm.hpp>
#include<vector>
using namespace glm;

#include"DataModel.h"

class Camera;
class MyScene;
class Light;

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
	//map<string, weak_ptr<Camera>>cameraList;
	std::vector<shared_ptr<Light>> lightList;
	weak_ptr<Camera> mainCamera;
public:
	void SetCurrentScene(shared_ptr<MyScene> scene) { currentScene = scene; }
	void SetMainCamera(shared_ptr<Camera> camera)
	{
		mainCamera = camera;
	}
public:
	shared_ptr<MyScene> GetCurrentScene()
	{
		// 检测弱指针所指对象是否已经销毁
		if (!currentScene.expired())
			return currentScene.lock();
		return nullptr;
	}

	shared_ptr<Camera> GetMainCamera()
	{
		if (!mainCamera.expired())
			return mainCamera.lock();
		return nullptr;
	}

	std::vector<shared_ptr<Light>>& GetLightList()
	{
		return lightList;
	}
};