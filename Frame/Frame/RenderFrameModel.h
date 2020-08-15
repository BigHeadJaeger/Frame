#pragma once
#include<iostream>
#include<glm.hpp>
using namespace glm;

#include"DataModel.h"

class Camera;
class MyScene;

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
		//auto it = cameraList.find("MainCamera");
		//if (it != cameraList.end())
		//	if (!it->second.expired())
		//		return it->second.lock();

		if (!mainCamera.expired())
			return mainCamera.lock();
		return nullptr;
	}
};