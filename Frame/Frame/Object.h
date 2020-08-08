#pragma once
#include<string>
#include<memory>
#include<OpenMesh/Core/IO/MeshIO.hh>
#include<OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
using namespace std;
#include"Renderer.h"
//#include"MarchingCube.h"
#include"DistributeFun.h"

// �����ͽ�ÿ��object�ֿ� Camera
//enum class OBJECTKIND
//{
//	OBJ_
//};


//����Object
class Object
{
protected:
	string name;									//object����
	Transform transformation;						//�Ϳռ�λ���йص�transform���
	shared_ptr<ShaderData> shaderData;							//ÿһ���������Ⱦ���ݣ��˴�Ϊ������࣬ʹ�ò�ͬ��Ⱦ��ʱ��ʼ��Ϊ��Ӧ����
	Renderer* renderer;								//ֻ��һ��ָ�룬��ͬ����Ⱦ�����ǵ���,��ͬ�������ʼ��ʱֻ��Ҫ����ָ�븳ֵ����
protected:
	//void UpdateMatrix() { shaderData->UpdateMatrix(transformation); }
public:
	Object()
	{
		//shaderData = NULL;
		renderer = NULL;
	}

	~Object()
	{
		//delete shaderData;
	}
	//Get
	string GetName() { return name; }
	Transform& GetTransform() { return transformation; }
	auto GetShaderData() { return shaderData; }
	//Set
	void SetName(string _name) { name = _name; }
	void SetRenderer(RENDERERTYPE type);			//������Ⱦ�������ɶ�Ӧ��shaderData

	virtual void InitBufferData() = 0;
	//virtual void UpdateBufferData() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
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
