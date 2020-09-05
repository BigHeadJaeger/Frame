#pragma once
#include<functional>
#include"RenderFrameModel.h"
#include"Object.h"

class Object;

class ObjectManager
{
private:
	size_t boxCount = 0;
	size_t sphereCount = 0;
	size_t gridCount = 0;

public:
	//shared_ptr<Object> root;
	vector<shared_ptr<Object>> objects;


	ObjectManager()
	{
		//shared_ptr<Object> rootObject(new Object);
		//rootObject->SetName("scene");
		//root = rootObject;
		//rootObject->parent.reset();
	}

public:
	shared_ptr<Object> GetObject(string name)
	{

	}

	void InsertObject(shared_ptr<Object> object)
	{
		objects.push_back(object);
	}

	shared_ptr<Object> GridObject(float width = 1, float height = 1, int m = 10, int n = 10);
	shared_ptr<Object> BoxObject(float width = 1, float height = 1, float depth = 1);
	shared_ptr<Object> SphereObject(float radius = 1, int slice = 40, int stack = 40);

	//void RemoveObject(shared_ptr<Object> object)
	//{
	//	auto it = objects.begin();
	//	while (it != objects.end())
	//	{
	//		if (*it == object)
	//		{
	//			//it->reset();
	//			it = objects.erase(it);
	//		}
	//			
	//		else
	//			it++;
	//	}
	//}
};