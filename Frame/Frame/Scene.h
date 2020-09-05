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

	// ��ǰ�����ĸ�����
	shared_ptr<Object> rootObject;

	ScreenRender screenRender;

	SkyBox skyBox;
public:
	MyScene()
	{
		// ÿ����������һ�����ڵ�
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

	void Init();			//��ʼ��������Ϣ
	void InitKeys();
	void ModelInit();
	void MaterialInit();
	void SkyBoxInit();
	// ��ʼ����Ļ��Ⱦ
	void ScreenRenderInit();

	void Update(float& dt);			//��Ҫ����ʱ��������־�����ʱ������shader�У�
	void Draw();					// �ܵĻ��ƣ������������ƣ� ��Ļ��Ⱦ�ȣ�

	void DrawScene();				// ���Ƴ���
public:
	void Scene1Init();
	void Scene2Init();
};