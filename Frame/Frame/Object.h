#pragma once
#include<string>
#include<memory>
#include<map>
#include<glad/glad.h>
#include<iostream>
using namespace std;
#include"Renderer.h"
#include"LightComponent.h"
//#include"MarchingCube.h"
//#include"DistributeFun.h"
//#include"Component.h"
//#include"RenderFrameModel.h"

// �����ͽ�ÿ��object�ֿ� Camera
enum class TAG
{
	DEFAULT,
	MAIN_CAMERA
};

//����Object��Ŀǰֻ����������Ⱦ�����壬����gameobject��
class Object
{
public:
	string name;									//object����
	string tag;
	bool isActive = true;
	// ��������ͨ�����Ʋ�ѯ
	map<string, shared_ptr<Component>> components;

	shared_ptr<Transform> transform;
public:
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
		if (!isActive)
			return;
		// ����ĸ���
		for (auto it = components.begin(); it != components.end(); it++)
			it->second->Update(dt);
	}

	void Draw()
	{
		if (!isActive)
			return;
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
		{
			auto tran = make_shared<Transform>();
			component = tran;
			transform = tran;
		}
		else if (type == COMPONENT_MESHREFERENCE)
			component = make_shared<MeshReference>();
		else if (type == COMPONENT_MESHRENDER)
			component = make_shared<MeshRenderer>();
		else if (type == COMPONENT_LIGHT)
		{
			auto lightComponent = make_shared<LightComponent>();
			component = lightComponent;
			RenderFrameModel::GetInstance().PushLight(lightComponent);
		}

		component->object = this;
		components.insert(make_pair(type, component));

		return component;
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

public:
	//Set
	void SetName(string _name)
	{
		name = _name;
	}


	void SetPosition(vec3&& pos)
	{
		transform->SetPosition(pos);
	}
	void SetPosition(vec3& pos)
	{
		transform->SetPosition(pos);
	}

public:
	//Get
	string GetName() { return name; }

	shared_ptr<Transform> GetTransform() { return dynamic_pointer_cast<Transform>(GetComponentByName(COMPONENT_TRANSFORM)); }
	shared_ptr<MeshReference> GetMeshReference() { return dynamic_pointer_cast<MeshReference>(GetComponentByName(COMPONENT_MESHREFERENCE)); }
	shared_ptr<MeshRenderer> GetMeshRender() { return dynamic_pointer_cast<MeshRenderer>(GetComponentByName(COMPONENT_MESHRENDER)); }

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

	const vec3& GetPosition()
	{
		return transform->position;
	}

	template<typename TYPE>
	shared_ptr<TYPE> GetComponent()
	{
		auto requireName = typeid(TYPE).name();

		shared_ptr<Component> res = nullptr;
		for (auto component : components)
		{
			auto targetName = typeid(*component.second.get()).name();
			if (targetName == requireName)
			{
				res = component.second;
				break;
			}
		}
		if (res)
			return dynamic_pointer_cast<TYPE>(res);
		else
			cout << "The specified component could not be found" << endl;

		return nullptr;
	}
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
