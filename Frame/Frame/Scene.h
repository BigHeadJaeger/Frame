#pragma once
#include<map>
using namespace std;
#include"ObjectManager.h"
#include"RenderFrameModel.h"
#include"Interaction.h"
#include"RenderQueue.h"

struct DrawMode
{
	bool isLine;
};
class MyScene
{
private:
	//各种场景信息（相机、材质、灯光、各种物体的各种矩阵）
	//map<string, Object*> objects;
	//map<string, map<string, shared_ptr<Object>>> objectManager;
	
	//map<string, shared_ptr<Object>> objects;
	RenderQueue renderQueue;
	
public:
	map<KEYNAME, Key> keys;

	Mouse mouse;

	DrawMode drawMode;

	ObjectManager objectManager;

	// 当前场景的根物体
	shared_ptr<Object> rootObject;
	//---------------------------------------------------------------------------------

private:

public:
	MyScene()
	{
		// 每个场景创建一个根节点
		shared_ptr<Object> root = make_shared<Object>();
		root->AddComponent<Transform>();
		rootObject = root;
		root->SetName("scene");
		objectManager.InsertObject(root);
		//shared_ptr<Object> rootObject(new Object);
		////root = rootObject;s
		//rootObject->parent.reset();
		//rootObject->name = "scene";
		//objects.insert(make_pair(rootObject->name, rootObject));
	}

	~MyScene()
	{
		//map<string, shared_ptr<Object>>::iterator objs_it;
		//for (objs_it = objects.begin(); objs_it != objects.end(); objs_it++)
		//{
		//	(*objs_it).second.reset();
		//	//delete (*objs_it).second;
		//}
		//objects.clear();
	}

	void UpdateObject(shared_ptr<Object> obj, float dt);
	//void RenderObject(shared_ptr<Object> obj);

	void Init();			//初始化各种信息
	void InitKeys();
	void ModelInit();
	void MaterialInit();

	void Update(float& dt);			//需要动画时，计算各种矩阵（暂时不传入shader中）
	void Draw();					//绘制场景
private:
};