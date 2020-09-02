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
#include"FileInterface.h"

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
	ScreenRenderInit();

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
	light1->SetPosition(vec3(-3, 3, 0));
	auto light1Component = light1->AddComponent<LightComponent>();
	//light1Component->SetLightType(LIGHT_TYPE::POINT_LIGHT);

	//shared_ptr<Object> light2 = make_shared<Object>();
	//light2->AddComponent<Transform>();
	//light2->SetName("light2");
	//rootObject->AddChild(light2);
	//light2->SetPosition(vec3(1, 2, 0));
	//auto light2Component = light2->AddComponent<LightComponent>();
	//light2Component->SetLightType(LIGHT_TYPE::POINT_LIGHT);

	//shared_ptr<Object> box(new Object);
	//box->AddComponent<Transform>();
	//box->SetPosition(vec3(-1, 0, 0));
	//box->transform->SetRotation(vec3(0, 60, 0));
	//rootObject->AddChild(box);
	//box->SetName("box1");
	//auto meshReference = box->AddComponent<MeshReference>();
	//meshReference->CreateBox(1, 1, 1);
	//auto bR = box->AddComponent<MeshRenderer>();
	//box->isSelect = true;
	//bR->material = MaterialManager::GetInstance().GetMaterial("metalgrid");

	shared_ptr<DefaultSpecularMaterial> specularMa = make_shared<DefaultSpecularMaterial>();
	//specularMa->SetTextureBase("Material\\btn_sz.png");
	specularMa->SetTextureBase(file::GetResPath("Material/blending_transparent_window.png"));
	//specularMa->SetTextureBase("Material\\oakfloor\\basecolor.png");


	//shared_ptr<Object> grid2 = make_shared<Object>();
	//grid2->SetName("grid2");
	//grid2->AddComponent<Transform>();
	//grid2->SetPosition(vec3(0, -0.5, 0));
	//auto grid2MR = grid2->AddComponent<MeshReference>();
	//grid2MR->CreateGrid(1, 1, 10, 10);
	//auto grid2MRE = grid2->AddComponent<MeshRenderer>();
	//rootObject->AddChild(grid2);
	//grid2MRE->material = MaterialManager::GetInstance().GetMaterial("defaultSpecular");

	auto box = objectManager.BoxObject();
	rootObject->AddChild(box);
	box->SetPosition(vec3(1, 0, 0));
	box->GetComponent<MeshRenderer>()->material = MaterialManager::GetInstance().GetMaterial("oakfloor");
	//box->isSelect = true;

	//auto grid2 = objectManager.GridObject(1, 1);
	//rootObject->AddChild(grid2);
	//grid2->SetPosition(vec3(-1, -0.5, 0));
	//grid2->transform->SetRotation(vec3(90, 0, 0));
	//grid2->GetComponent<MeshRenderer>()->material = MaterialManager::GetInstance().GetMaterial("TransparentSpecular");

	//auto grid3 = objectManager.GridObject(1, 1);
	//rootObject->AddChild(grid3);
	//grid3->SetPosition(vec3(0, -0.5, 1));
	//grid3->transform->SetRotation(vec3(90, 0, 0));
	//grid3->GetComponent<MeshRenderer>()->material = MaterialManager::GetInstance().GetMaterial("TransparentSpecular");
	//grid3->isSelect = true;

	auto grid1 = objectManager.GridObject(10, 10);
	rootObject->AddChild(grid1);
	grid1->SetPosition(vec3(0, -1, 0));
	grid1->GetComponent<MeshRenderer>()->material = MaterialManager::GetInstance().GetMaterial("metalgrid");

	//grid2MRE->material = specularMa;
	
	//decltype(auto) modelGenerator = ModelGenerator::GetInstance();
	//auto testModel = modelGenerator.Create(file::GetResPath("Model/nanosuit/nanosuit.obj"));
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
	//keys.insert(pair<KEYNAME, Key>(BTN2, Key(BTN2)));
	//keys.insert(pair<KEYNAME, Key>(BTN3, Key(BTN3)));
	//keys.insert(pair<KEYNAME, Key>(BTN4, Key(BTN4)));
	//keys.insert
	//keys.push_back(Key(BTNW));
}

void MyScene::ModelInit()
{
	decltype(auto) modelManager = ModelManager::GetInstance();
	//modelManager.InitModel("OBJ\\Neptune.obj");
	//modelManager.InitModel("Model\\backpack\\backpack.obj");
	//modelManager.InitModel(file::GetResPath("Model/nanosuit/nanosuit.obj"));
	
}

void MyScene::MaterialInit()
{
	decltype(auto) materialManager = MaterialManager::GetInstance();

	materialManager.CreateMaterial<NoneMaterial>("none");

	auto material1 = materialManager.CreateMaterial<PBRMaterial>("metalgrid");
	material1->SetTextureBase(file::GetResPath("Material/metalgrid/basecolor.png"));
	material1->SetTextureNormal(file::GetResPath("Material/metalgrid/normal.png"));
	material1->SetTextureMetallic(file::GetResPath("Material/metalgrid/metallic.png"));
	material1->SetTextureAO(file::GetResPath("Material/metalgrid/AO.png"));
	material1->SetTextureRoughness(file::GetResPath("Material/metalgrid/roughness.png"));

	auto material2 = materialManager.CreateMaterial<PBRMaterial>("TransparentSpecular");
	material2->SetTextureBase(file::GetResPath("Material/blending_transparent_window.png"));
	material2->SetRenderMode(RenderMode::Transparent);

	auto material3 = materialManager.CreateMaterial<DefaultSpecularMaterial>("DefaultSpecular");
	material3->SetTextureBase("");

	auto material4 = materialManager.CreateMaterial<PBRMaterial>("oakfloor");
	material4->SetTextureBase(file::GetResPath("Material/oakfloor/basecolor.png"));
}

void MyScene::ScreenRenderInit()
{
	screenRender.InitDefaultFrameBuffer();
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
		if(*it)
			UpdateObject(*it, dt);
	}
}



void MyScene::Draw()
{
	if (screenRender.isOpen)
	{
		screenRender.RenderToFBO([&]() {
			DrawScene();
			});
		screenRender.Render();
	}
	else
	{
		DrawScene();
	}

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X)
}

void MyScene::DrawScene()
{
	//绘制,包含缓冲区的清空，各种效果的开启（blend、 cull之类的）
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//glEnable(GL_BLEND);
	// 源在上， 目标在下， 混合公式Cs * Fs + Ct * (1 - Fs)
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	renderQueue.Render(rootObject);
	//RenderObject(rootObject);

}

void MyScene::RenderObject(shared_ptr<Object> obj)
{
	obj->Draw();
	for (auto it = obj->children.begin(); it != obj->children.end(); it++)
	{
		if (*it)
			RenderObject(*it);
	}
}