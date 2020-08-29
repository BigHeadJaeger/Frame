#pragma once
#include<string>
#include<memory>
#include<map>
#include<glad/glad.h>
#include<iostream>
#include<list>
using namespace std;
#include"Renderer.h"
#include"LightComponent.h"
#include"ObjectManager.h"
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
class Object : public std::enable_shared_from_this<Object>
{
public:
	string name;									//object����
	string tag;
	bool isActive = true;
	// ��������ͨ�����Ʋ�ѯ
	map<string, shared_ptr<Component>> components;
	shared_ptr<Transform> transform;

	//Object* parent;
	//list<Object*> children;
	weak_ptr<Object> parent;
	list<weak_ptr<Object>> children;
public:
	Object()
	{
		//// ÿ������Ĭ�����������
		//AddComponent<Transform>();
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

		auto meshRender = GetComponent<MeshRenderer>();
		if (meshRender)
			meshRender->Render();
	}

	template<typename TYPE>
	shared_ptr<TYPE> AddComponent()
	{
		string typeName = typeid(TYPE).name();
		auto it = components.find(typeName);
		if (it != components.end())
		{
			cout << "the specify component has been added" << endl;
			return nullptr;
		}

		auto component = make_shared<TYPE>();
		component->object = shared_from_this();
		if (typeName == "class Transform")
			transform = dynamic_pointer_cast<Transform>(component);
		else if (typeName == "class LightComponent")
		{
			RenderFrameModel::GetInstance().PushLight(dynamic_pointer_cast<LightComponent>(component));
		}

		components.insert(make_pair(typeid(TYPE).name(), component));

		return component;
	}

	template<typename TYPE>
	bool isComponent()
	{
		auto it = components.find(typeid(TYPE).name());
		if (it != components.end())
			return true;
		else
			return false;
	}

	void AddChild(shared_ptr<Object> obj)
	{
		auto self_ptr = shared_from_this();
		if (!obj->parent.expired())
		{
			cout << "the object has been added" << endl;
			return;
		}
		children.push_back(obj);
		obj->parent = self_ptr;
		
		// ��һ������������νṹ��ʱ���䱣����manager��
		decltype(auto) manager = RenderFrameModel::GetInstance().GetCurrentObjectManager();
		manager.InsertObject(obj);
	}

	// ����Ӹ��ڵ����Ƴ�
	void RemoveFromParent()
	{
		if (parent.expired())
		{
			cout << "This object has no parent" << endl;
			return;
		}

		auto it = parent.lock()->children.begin();
		while (it != parent.lock()->children.end())
		{
			if (it->lock() == shared_from_this())
			{
				it = parent.lock()->children.erase(it);
				decltype(auto) manager = RenderFrameModel::GetInstance().GetCurrentObjectManager();
				manager.RemoveObject(shared_from_this());
			}
			else
				it++;
		}

		parent.reset();
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

	bool IsActive() { return isActive; }

	const vec3& GetPosition()
	{
		return transform->position;
	}

	template<typename TYPE>
	shared_ptr<TYPE> GetComponent()
	{
		auto requireName = typeid(TYPE).name();
		auto it = components.find(requireName);
		if (it != components.end())
			return dynamic_pointer_cast<TYPE>(it->second);

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
