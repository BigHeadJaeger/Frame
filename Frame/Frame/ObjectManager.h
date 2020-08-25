#pragma once
#include<functional>
#include"RenderFrameModel.h"
#include"Object.h"

class ObjectManager
{
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
};