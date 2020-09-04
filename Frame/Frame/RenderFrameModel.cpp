#include "RenderFrameModel.h"
#include"Scene.h"

shared_ptr<Object> RenderFrameModel::GetSceneRoot()
{
	if (!currentScene.expired())
	{
		auto scene = currentScene.lock();
		return scene->rootObject;
	}
	cout << "scene do not exist" << endl;
	return nullptr;
}

ObjectManager& RenderFrameModel::GetCurrentObjectManager()
{
	return currentScene.lock()->objectManager;
}
