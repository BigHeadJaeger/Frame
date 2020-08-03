#pragma once
#include "Scene.h"
#include"MeshObject.h"
#include<GLFW\glfw3.h>

void MyScene::Init()
{

	//glGetString(GL_RENDERER);
	//��ʼ��glew
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "initialize glad failed" << std::endl;
		return;
	}
	//glewInit();
	//��ʼ��Renderer�е�program
	PBRRenderer::GetRenderer().InitProgram("SF_PBR.v", "SF_PBR.f");
	//SimpleRenderer::GetRenderer()->InitProgram("SF_SimpleColor.v", "SF_SimpleColor.f");
	//SimpleRenderer::GetRenderer()->InitProgram("SF_VertexColor.v", "SF_VertexColor.f");
	VertexColorRender::GetRenderer().InitProgram("SF_VertexColor.v", "SF_VertexColor.f");

	//pShadowTex.SetShader("shadowTex.v", "shadowTex.f");


	////ָ����Դ����
	lightPos = vec3(-3, 5, 3);
	lightColor = vec3(400.f, 400.f, 400.f);

	//��ʼ�������
	//mainCamera = new Camera();
	MainCamera::GetInstance().Init(vec3(0, 2, 3), vec3(0, 0, 0));

	//SetDrawMode(drawMode.isLine, false);
	drawMode.isLine = false;

	//ָ������PBR����
	//MeshObject* cow = new MeshObject();
	//cow->SetName("cow");
	//cow->readObjFile("Resource\\OBJ\\cow.obj");
	//cow->SetRenderer(SIMPLE);
	//cow->InitBufferData();
	//cow->GetTransform().SetPosition(vec3(0, 0, 0));
	//cow->GetTransform().SetScaler(vec3(2.0));
	//dynamic_cast<SimpleShaderData*>(cow->GetShaderData())->SetColor(vec3(255, 0, 0));
	//objects.insert(pair<string, Object*>(cow->GetName(), cow));

	//shared_ptr<MeshObject> cow(new MeshObject());
	//cow->SetName("cow");
	//cow->readObjFile("OBJ\\cow.obj");
	//cow->SetRenderer(VERTEXCOLOR);
	//cow->InitBufferData();
	//cow->GetTransform().SetPosition(vec3(1, 0, 1));
	//cow->GetTransform().SetScaler(vec3(2.0));
	//objects.insert(pair<string, shared_ptr<Object>>(cow->GetName(), cow));

	//MPSWaterParticleGroup* water = new MPSWaterParticleGroup();
	//water->SetName("water");
	//water->SetRenderer(SIMPLERENDER);
	//water->GetTransform().SetPosition(vec3(0.5));
	//water->SetDiameter(0.01);
	//water->SetViscosity(0.000001);
	//water->InitParticles();
	//dynamic_cast<SimpleShaderData*>(water->GetShaderData())->SetColor(vec3(0, 0, 200));
	//objects.insert(pair<string, Object*>(water->GetName(), water));


	//Metaball* balls = new Metaball();
	//balls->SetName("Metaball");
	//balls->SetRenderer(SIMPLERENDER);
	//balls->GetTransform().SetPosition(vec3(-0, -0, 0));
	//balls->SetSourcePoints(vec3(0.1), 2, 1, 2);
	//balls->SetRadius(0.005);
	////balls->GetTransform().SetScaler(vec3(3.0));
	//dynamic_cast<SimpleShaderData*>(balls->GetShaderData())->SetColor(vec3(0, 0, 255));
	//objects.insert(pair<string, Object*>(balls->GetName(), balls));


	shared_ptr<MeshObject> cube(new MeshObject());
	cube->SetName("Cube");
	cube->InitBox(1, 1, 1);
	cube->SetRenderer(PBR);
	cube->InitBufferData();
	cube->GetTransform().SetPosition(vec3(0, 0, 0));
	cube->GetTransform().SetScaler(vec3(1));
	auto cubeShaderData = dynamic_pointer_cast<PBRShaderData>(cube->GetShaderData());
	cubeShaderData->SetTextureState(true);
	cubeShaderData->SetAlbedoState(true);
	cubeShaderData->InitTexture(ALBEDO, "Material\\metalgrid\\basecolor.png");
	cubeShaderData->SetNormalState(true);
	cubeShaderData->InitTexture(NORMAL, "Material\\metalgrid\\normal.png");
	cubeShaderData->SetAOState(true);
	cubeShaderData->InitTexture(AO, "Material\\metalgrid\\AO.png");
	cubeShaderData->SetRoughnessState(true);
	cubeShaderData->InitTexture(ROUGHNESS, "Material\\metalgrid\\roughness.png");
	cubeShaderData->SetMetallicState(true);
	cubeShaderData->InitTexture(METALLIC, "Material\\metalgrid\\metallic.png");
	objects.insert(pair<string, shared_ptr<Object>>(cube->GetName(), cube));

	shared_ptr<MeshObject> grid(new MeshObject());
	grid->SetName("Floor");
	grid->InitGrid(10, 10, 10, 10);
	grid->SetRenderer(PBR);
	grid->InitBufferData();
	grid->GetTransform().SetPosition(vec3(0, -0.5, 0));
	grid->GetTransform().SetScaler(vec3(1));
	auto gridShaderData = dynamic_pointer_cast<PBRShaderData>(grid->GetShaderData());
	gridShaderData->SetTextureState(true);
	gridShaderData->SetAlbedoState(true);
	gridShaderData->InitTexture(ALBEDO, "Material\\oakfloor\\basecolor.png");
	gridShaderData->SetNormalState(true);
	gridShaderData->InitTexture(NORMAL, "Material\\oakfloor\\normal.png");
	gridShaderData->SetAOState(true);
	gridShaderData->InitTexture(AO, "Material\\oakfloor\\AO.png");
	gridShaderData->SetRoughnessState(true);
	gridShaderData->InitTexture(ROUGHNESS, "Material\\oakfloor\\roughness.png");
	objects.insert(pair<string, shared_ptr<Object>>(grid->GetName(), grid));


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

	//�����ӽǾ���
	MainCamera::GetInstance().SetView();
	//����ͶӰ����
	MainCamera::GetInstance().SetPro();

	//��������object���¾���
	for (auto objs_it = objects.begin(); objs_it != objects.end(); objs_it++)
	{
		(*objs_it).second->Update(dt);
	}

	//��������key����ִ��key��ǰ�󶨵��¼�
	for (auto keys_it = keys.begin(); keys_it != keys.end(); keys_it++)
	{
		keys_it->second.Execute();
	}
}

void MyScene::Draw()
{

	//NormalShadowMap();

	//����ÿһ������ʱ���Ƚ����еĸ������������ؾ��󣬲��ʵ���Ϣ����shader��


	//����,��������������գ�����Ч���Ŀ�����blend�� cull֮��ģ�
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);					//��ά����Ҫ���������޳�

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

	//glUseProgram(p1.p);						//������ɫ������

	for (auto objs_it = objects.begin(); objs_it != objects.end(); objs_it++)
	{
		(*objs_it).second->Draw();
	}

}