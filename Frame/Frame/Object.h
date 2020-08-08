#pragma once
#include<string>
#include<memory>
#include<OpenMesh/Core/IO/MeshIO.hh>
#include<OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
using namespace std;
#include"Renderer.h"
//#include"MarchingCube.h"
#include"DistributeFun.h"

// 按类型将每个object分开 Camera
//enum class OBJECTKIND
//{
//	OBJ_
//};


//基类Object
class Object
{
protected:
	string name;									//object名称
	Transform transformation;						//和空间位置有关的transform组件
	shared_ptr<ShaderData> shaderData;							//每一个物体的渲染数据，此处为抽象基类，使用不同渲染器时初始化为相应子类
	Renderer* renderer;								//只是一个指针，不同的渲染器都是单例,不同的物体初始化时只需要将此指针赋值就行
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
	void SetRenderer(RENDERERTYPE type);			//设置渲染器并生成对应的shaderData

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
