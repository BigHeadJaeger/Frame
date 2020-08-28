#pragma once
#include "Scene.h"
//#include"MeshObject.h"
//#include"Object.h"
#include<GLFW\glfw3.h>
#include<iostream>
#include"RenderFrameModel.h"
#include"ModelManager.h"
#include"ModelGenerator.h"
#include"MaterialManager.h"

void MyScene::Init()
{

	//glGetString(GL_RENDERER);
	//初始化glew
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "initialize glad failed" << std::endl;
		return;
	}

	ModelInit();
	MaterialInit();

	drawMode.isLine = false;



	shared_ptr<Object> mainCamera = make_shared<Object>();
	mainCamera->AddComponent<Transform>();
	rootObject->AddChild(mainCamera);
	mainCamera->SetName("MainCamera");
	mainCamera->SetPosition(vec3(0, 2, 3));
	auto cameraComponent = mainCamera->AddComponent<Camera>();
	cameraComponent->Init(vec3(0, 0, 0));
	RenderFrameModel::GetInstance().SetMainCamera(cameraComponent);
	//objectManager.InsertObject(mainCamera);
	//objects.insert(make_pair(mainCamera->GetName(), mainCamera));


	shared_ptr<Object> light1 = make_shared<Object>();
	light1->AddComponent<Transform>();
	light1->SetName("light1");
	rootObject->AddChild(light1);
	light1->SetPosition(vec3(-3, 2, 0));
	auto light1Component = light1->AddComponent<LightComponent>();
	light1Component->SetLightType(LIGHT_TYPE::POINT_LIGHT);

	//shared_ptr<Object> light2 = make_shared<Object>();
	//light2->AddComponent<Transform>();
	//light2->SetName("light2");
	//rootObject->AddChild(light2);
	//light2->SetPosition(vec3(3, 2, 0));
	//auto light2Component = light2->AddComponent<LightComponent>();
	//light2Component->SetLightType(LIGHT_TYPE::POINT_LIGHT);

	shared_ptr<Object> box(new Object);
	box->AddComponent<Transform>();
	box->SetPosition(vec3(-1, 0, 0));
	box->transform->SetRotation(vec3(0, 60, 0));
	rootObject->AddChild(box);
	box->SetName("box1");
	auto meshReference = box->AddComponent<MeshReference>();
	meshReference->CreateBox(1, 1, 1);
	auto bR = box->AddComponent<MeshRenderer>();
	bR->material = MaterialManager::GetInstance().GetMaterial("metalgrid");

	//shared_ptr<Object> box2 = make_shared<Object>();
	//box2->SetName("box2");
	//box2->AddComponent<Transform>();
	//box2->SetPosition(vec3(0, 0, 0));
	//rootObject->AddChild(box2);
	//auto box2MeshR = box2->AddComponent<MeshReference>();
	//box2MeshR->CreateBox(0.5, 0.5, 0.5);
	//auto box2MeshRen = box2->AddComponent<MeshRenderer>();
	//shared_ptr<DefaultSpecularMaterial> specularMa = make_shared<DefaultSpecularMaterial>();
	//specularMa->SetTextureBase("");
	//box2MeshRen->material = specularMa;


	//decltype(auto) modelGenerator = ModelGenerator::GetInstance();
	//auto testModel = modelGenerator.Create("Model\\nanosuit\\nanosuit.obj");
	//testModel->transform->SetScaler(vec3(0.1));

	//rootObject->AddChild(testModel);
}

void MyScene::InitKeys()
{
	keys.insert(pair<KEYNAME, Key>(BTNW, Key(BTNW)));
	keys.insert(pair<KEYNAME, Key>(BTNA, Key(BTNA)));
	keys.insert(pair<KEYNAME, Key>(BTNS, Key(BTNS)));
	keys.insert(pair<KEYNAME, Key>(BTND, Key(BTND)));
	keys.insert(pair<KEYNAME, Key>(BTN1, Key(BTN1)));
	//keys.insert
	//keys.push_back(Key(BTNW));
}

void MyScene::ModelInit()
{
	decltype(auto) modelManager = ModelManager::GetInstance();
	//modelManager.InitModel("OBJ\\Neptune.obj");
	//modelManager.InitModel("Model\\backpack\\backpack.obj");
	//modelManager.InitModel("Model\\nanosuit\\nanosuit.obj");
	
}

void MyScene::MaterialInit()
{
	decltype(auto) materialManager = MaterialManager::GetInstance();
	auto material1 = materialManager.CreateMaterial<PBRMaterial>("metalgrid");
	material1->SetTextureBase("Material\\metalgrid\\basecolor.png");
	material1->SetTextureNormal("Material\\metalgrid\\normal.png");
	material1->SetTextureMetallic("Material\\metalgrid\\metallic.png");
	material1->SetTextureAO("Material\\metalgrid\\AO.png");
	material1->SetTextureRoughness("Material\\metalgrid\\roughness.png");

	materialManager.CreateMaterial<NoneMaterial>("none");
}

void MyScene::Update(float& dt)
{
	// 从场景中的根节点遍历所有object，进行更新
	UpdateObject(rootObject, dt);

	// 按键事件带来的变换会在下一帧起效
	// 遍历所有key，并执行key当前绑定的事件
	for (auto keys_it = keys.begin(); keys_it != keys.end(); keys_it++)
	{
		keys_it->second.Execute();
	}
}

void MyScene::UpdateObject(shared_ptr<Object> obj, float dt)
{
	//if(obj)
	obj->Update(dt);
	for (auto it = obj->children.begin(); it != obj->children.end(); it++)
	{
		if(!it->expired())
			UpdateObject(it->lock(), dt);
	}
}



void MyScene::Draw()
{

	//NormalShadowMap();

	//绘制每一个物体时，先将类中的该物体的所有相关矩阵，材质等信息传入shader中


	//绘制,包含缓冲区的清空，各种效果的开启（blend、 cull之类的）
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);					//三维物体要开启背面剔除

	if (drawMode.isLine)
	{
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//glFrontFace(GL_CW);
	//glCullFace(GL_FRONT);

	//glUseProgram(p1.p);						//启用着色器程序
	//for (auto objs_it = objects.begin(); objs_it != objects.end(); objs_it++)
	//{
	//	objs_it->second->Draw();
	//}

	RenderObject(rootObject);
}

void MyScene::RenderObject(shared_ptr<Object> obj)
{
	obj->Draw();
	for (auto it = obj->children.begin(); it != obj->children.end(); it++)
	{
		if (!it->expired())
			RenderObject(it->lock());
	}
}