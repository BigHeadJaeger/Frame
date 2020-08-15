#pragma once
#include<string>
#include<memory>
#include<map>
#include<glad/glad.h>
#include<iostream>
using namespace std;
#include"Renderer.h"
//#include"MarchingCube.h"
//#include"DistributeFun.h"
//#include"Component.h"
//#include"RenderFrameModel.h"

// �����ͽ�ÿ��object�ֿ� Camera
//enum class OBJECTKIND
//{
//	OBJ_
//};

//#include"Component.h"
//#include"Camera.h"
//#include"Transform.h"


//����Object��Ŀǰֻ����������Ⱦ�����壬����gameobject��
class Object
{
protected:
	string name;									//object����
	// ��������ͨ�����Ʋ�ѯ
	map<string, shared_ptr<Component>> components;
public:
	void test()
	{
		cout << components["Transform"]->object->name << endl;
	}

	Object()
	{
		// ÿ������Ĭ�����������
		AddComponent(COMPONENT_TRANSFORM);
	}

	~Object()
	{
	}

	void Update(float dt)
	{
		// ����ĸ���
		for (auto it = components.begin(); it != components.end(); it++)
			it->second->Update(dt);
	}

	void Draw()
	{
		if (isComponent(COMPONENT_MESHRENDER))
		{
			auto render = dynamic_pointer_cast<MeshRenderer>(components[COMPONENT_MESHRENDER]);
			render->Render();
		}
	}

	template<typename S>
	shared_ptr<Component> AddComponent(S&& type)
	{
		shared_ptr<Component> component;

		if (type == COMPONENT_CAMERA)
			component = make_shared<Camera>();
		else if (type == COMPONENT_TRANSFORM)
			component = make_shared<Transform>();

		component->object = this;
		components.insert(make_pair(type, component));

		return component;
	}

	shared_ptr<Transform> GetTransform()
	{
		auto t = components[COMPONENT_TRANSFORM];
		return dynamic_pointer_cast<Transform>(t);
	}

	template<typename S>
	shared_ptr<Component> GetComponentByName(S&& name)
	{
		auto it = components.find(name);
		if (it != components.end())
			return it->second;
		else
			cout << "The specified component could not be found" << endl;
		return nullptr;
	}

	template<typename S>
	bool isComponent(S&& name)
	{
		auto it = components.find(name);
		if (it != components.end())
			return true;
		else
			return false;
	}

	//Get
	string GetName() { return name; }
	//Set
	void SetName(string _name) { name = _name; }
	//void SetRenderer(RENDERERTYPE type);			//������Ⱦ�������ɶ�Ӧ��shaderData
};


////Metaball
//class Metaball:public Object
//{
//private:
//	MarchingCube marchingCube;
//	vector<vec3> sourcePoints;
//
//	float temp;
//	vec3 initPos;
//
//	void GetVertexInfo(vector<float>& verticesInfo, bool& provideNormal, bool& provideTex);
//public:
//	Metaball()
//	{
//		temp = 0;
//	}
//	void SetSourcePoints(vec3 firstPos, int w, int h, int d);
//	void SetRadius(float r)
//	{
//		marchingCube.radius = r;
//	}
//
//	void InitBufferData()override;
//	void UpdateBufferData() override;
//	void Update(float dt)override;
//	void Draw()override;
//};
//
