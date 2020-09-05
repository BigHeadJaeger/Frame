#pragma once
#include<map>
using namespace std;
#include"ObjectManager.h"
#include"RenderFrameModel.h"
#include"Interaction.h"
#include"RenderQueue.h"
#include"ScreenRender.h"
#include"SkyBox.h"

struct DrawMode
{
	bool isLine;
};
class MyScene
{
private:
	RenderQueue renderQueue;
public:
	map<KEYNAME, Key> keys;
	Mouse mouse;

	DrawMode drawMode;

	ObjectManager objectManager;

	// 当前场景的根物体
	shared_ptr<Object> rootObject;

	ScreenRender screenRender;

	SkyBox skyBox;
public:
	MyScene()
	{
		// 每个场景创建一个根节点
		shared_ptr<Object> root = make_shared<Object>();
		root->AddComponent<Transform>();
		rootObject = root;
		root->SetName("scene");
		objectManager.InsertObject(root);
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
	void RenderObject(shared_ptr<Object> obj);

	void Init();			//初始化各种信息
	void InitKeys();
	void ModelInit();
	void MaterialInit();
	void SkyBoxInit();
	// 初始化屏幕渲染
	void ScreenRenderInit();

	void Update(float& dt);			//需要动画时，计算各种矩阵（暂时不传入shader中）
	void Draw();					// 总的绘制（包括场景绘制， 屏幕渲染等）

	void DrawScene();				// 绘制场景
public:
	void Scene1Init();
	void Scene2Init();
};