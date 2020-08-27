#pragma once
#include "Scene.h"
//#include"MeshObject.h"
//#include"Object.h"
#include<GLFW\glfw3.h>
#include<iostream>
#include"RenderFrameModel.h"
#include"ModelManager.h"
#include"ModelGenerator.h"

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


	//shared_ptr<Object> dirLight = make_shared<Object>();
	//dirLight->AddComponent<Transform>();
	//dirLight->SetName("DirLight");
	//rootObject->AddChild(dirLight);
	//dirLight->SetPosition(vec3(-3, 1, -2));
	//auto lightComponent = dirLight->AddComponent<LightComponent>();
	//lightComponent->SetLightType(LIGHT_TYPE::POINT_LIGHT);

	//shared_ptr<Object> box(new Object);
	//box->AddComponent<Transform>();
	//box->SetPosition(vec3(-1, 0, 0));
	//box->transform->SetRotation(vec3(0, 60, 0));
	//rootObject->AddChild(box);
	//box->SetName("box1");
	//auto meshReference = box->AddComponent<MeshReference>();
	//meshReference->CreateBox(1, 1, 1);
	//auto bR = box->AddComponent<MeshRenderer>();
	//shared_ptr<PBRMaterial> pbrMaterial1 = make_shared<PBRMaterial>();
	//pbrMaterial1->SetTextureBase("Material\\metalgrid\\basecolor.png");
	//pbrMaterial1->SetTextureNormal("Material\\metalgrid\\normal.png");
	//pbrMaterial1->SetTextureMetallic("Material\\metalgrid\\metallic.png");
	//pbrMaterial1->SetTextureAO("Material\\metalgrid\\AO.png");
	//pbrMaterial1->SetTextureRoughness("Material\\metalgrid\\roughness.png");
	//bR->material = pbrMaterial1;

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
	//auto testModel = modelGenerator.Create("OBJ\\Neptune.obj");
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
	modelManager.InitModel("OBJ\\Neptune.obj");
	
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