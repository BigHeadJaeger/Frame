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
	Transform transformation;						//�Ϳռ�λ���йص�transform���
	shared_ptr<ShaderData> shaderData;							//ÿһ���������Ⱦ���ݣ��˴�Ϊ������࣬ʹ�ò�ͬ��Ⱦ��ʱ��ʼ��Ϊ��Ӧ����
	Renderer* renderer;								//ֻ��һ��ָ�룬��ͬ����Ⱦ�����ǵ���,��ͬ�������ʼ��ʱֻ��Ҫ����ָ�븳ֵ����
	// ��������ͨ�����Ʋ�ѯ
	map<string, shared_ptr<Component>> components;
protected:
	//void UpdateMatrix() { shaderData->UpdateMatrix(transformation); }
public:
	Object()
	{
		renderer = NULL;
		// ÿ������Ĭ�����������
		components.insert(make_pair("Transform", make_shared<Transform>()));
	}

	~Object()
	{
		//delete shaderData;
	}

	virtual void InitBufferData() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;


	template<typename S>
	void AddComponent(S&& type)
	{
		if (type == COMPONENT_CAMERA)
			components.insert(make_pair(type, make_shared<Camera>()));
		else if (type == COMPONENT_TRANSFORM)
			components.insert(make_pair(type, make_shared<Transform>()));
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
