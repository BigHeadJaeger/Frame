#pragma once
#include<string>
#include<memory>
#include<OpenMesh/Core/IO/MeshIO.hh>
#include<OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include<map>
using namespace std;
#include"Renderer.h"
//#include"MarchingCube.h"
#include"DistributeFun.h"
#include"Component.h"

// �����ͽ�ÿ��object�ֿ� Camera
//enum class OBJECTKIND
//{
//	OBJ_
//};


//����Object��Ŀǰֻ����������Ⱦ�����壬����gameobject��
class Object
{
protected:
	string name;									//object����
	// ��������ͨ�����Ʋ�ѯ
	map<string, shared_ptr<Component>> components;

	
protected:
	//void UpdateMatrix() { shaderData->UpdateMatrix(transformation); }
public:
	Object()
	{
		// ÿ������Ĭ�����������
		AddComponent(COMPONENT_TRANSFORM);
		//components.insert(make_pair("Transform", make_shared<Transform>()));
	}

	~Object()
	{
		//delete shaderData;
	}

	virtual void InitBufferData() = 0;
	virtual void Update(float dt) = 0;
	void Draw()
	{
		if (isComponent(COMPONENT_MESHRENDER))
		{
			auto render = dynamic_pointer_cast<MeshRenderer>(components[COMPONENT_MESHRENDER]);

			
		}
	}


	template<typename S>
	void AddComponent(S&& type)
	{
		if (type == COMPONENT_CAMERA)
		{
			auto camera = make_shared<Camera>();
			camera->object = this;
			components.insert(make_pair(type, camera));
		}
		else if (type == COMPONENT_TRANSFORM)
		{
			auto transform = make_shared<Transform>();
			transform->object = this;
			components.insert(make_pair(type, transform));
		}
	}

	shared_ptr<Transform> GetTransform() { return dynamic_pointer_cast<Transform>(components[COMPONENT_TRANSFORM]); }

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
	//Transform& GetTransform() { return transformation; }
	auto GetShaderData() { return shaderData; }
	//Set
	void SetName(string _name) { name = _name; }
	void SetRenderer(RENDERERTYPE type);			//������Ⱦ�������ɶ�Ӧ��shaderData
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
