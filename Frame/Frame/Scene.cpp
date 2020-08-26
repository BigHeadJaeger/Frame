#pragma once
#include "Scene.h"
//#include"MeshObject.h"
//#include"Object.h"
#include<GLFW\glfw3.h>
#include<iostream>
#include"RenderFrameModel.h"
#include"Model.h"

void MyScene::Init()
{

	//glGetString(GL_RENDERER);
	//初始化glew
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "initialize glad failed" << std::endl;
		return;
	}
	//glewInit();
	//初始化Renderer中的program
	//PBRRenderer::GetRenderer().InitProgram("SF_PBR.v", "SF_PBR.f");
	//SimpleRenderer::GetRenderer()->InitProgram("SF_SimpleColor.v", "SF_SimpleColor.f");
	//SimpleRenderer::GetRenderer()->InitProgram("SF_VertexColor.v", "SF_VertexColor.f");
	//VertexColorRender::GetRenderer().InitProgram("SF_VertexColor.v", "SF_VertexColor.f");
	//DefaultRenderer::GetRenderer().InitProgram("SF_PBR.v", "SF_PBR.f");
	//DefaultRenderer::GetRenderer().InitProgram("SF_Phong.v", "SF_Phong.f");

	//pShadowTex.SetShader("shadowTex.v", "shadowTex.f");

	//初始化主相机
	//mainCamera = new Camera();
	//MainCamera::GetInstance().Init(vec3(0, 2, 3), vec3(0, 0, 0));

	//SetDrawMode(drawMode.isLine, false);
	drawMode.isLine = false;

	//auto root = RenderFrameModel::GetInstance().GetSceneRoot();


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



	//shared_ptr<Object> dirLight(new Object);
	//dirLight->SetName("DirLight");
	//dirLight->SetPosition(vec3(-3, 1, -2));
	//auto lightComponent = dirLight->AddComponent<LightComponent>();
	//dynamic_pointer_cast<DirLight>(lightComponent->light)->lightColor = vec3(150);
	//objects.insert(make_pair(dirLight->GetName(), dirLight));

	shared_ptr<Object> box(new Object);
	box->AddComponent<Transform>();
	rootObject->AddChild(box);
	box->SetName("box1");
	box->SetPosition(vec3(0, 0, 0));
	auto meshReference = box->AddComponent<MeshReference>();
	meshReference->CreateBox(1, 1, 1);
	auto bR = box->AddComponent<MeshRenderer>();
	//shared_ptr<DefaultSpecularMaterial> specularMaterial(new DefaultSpecularMaterial);
	//specularMaterial->SetTextureBase("");
	//specularMaterial->baseColor = vec4(255, 0, 0, 0);
	//box->GetComponent<MeshRenderer>()->material = specularMaterial;

	//objectManager.InsertObject(box);
	//objects.insert(make_pair(box->GetName(), box));

	//objectManager.RemoveObject(box);

	//box->RemoveFromParent();


	//shared_ptr<Object> model(new Object);
	//model->SetName("Model1");
	//auto modelMeshReference = model->AddComponent<MeshReference>();
	//model->transform->SetScaler(vec3(0.2, 0.2, 0.2));

	//Model testModel;
	//testModel.LoadModel("OBJ\\Neptune.obj");
	//modelMeshReference->SetMesh(testModel.meshs[0]);
	//model->AddComponent<MeshRenderer>();
	//objects.insert(make_pair(model->GetName(), model));
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

void MyScene::Update(float& dt)
{
	// 从场景中的根节点遍历所有object，进行更新
	UpdateObject(rootObject, dt);


	//// 遍历所有object更新矩阵
	//for (auto objs_it = objects.begin(); objs_it != objects.end(); objs_it++)
	//{
	//	objs_it->second->Update(dt);
	//}

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