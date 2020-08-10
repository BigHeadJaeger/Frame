#pragma once
#include<map>
using namespace std;
#include"Object.h"
//#include"ParticleGroup.h"
//#include"MPSWaterParticleGroup.h"
#include"Interaction.h"

struct DrawMode
{
	bool isLine;
};
class MyScene
{
private:
	//���ֳ�����Ϣ����������ʡ��ƹ⡢��������ĸ��־���
	//map<string, Object*> objects;
	map<string, map<string, shared_ptr<Object>>> objectManager;
	map<string, shared_ptr<Object>> objects;
	//MeshObject cow;
	//�ƹ�
	vec3 lightPos;
	vec3 lightColor;

public:
	//vector<Key> keys;
	map<KEYNAME, Key> keys;

	Mouse mouse;

	DrawMode drawMode;
	//---------------------------------------------------------------------------------

private:

public:
	~MyScene()
	{
		map<string, shared_ptr<Object>>::iterator objs_it;
		for (objs_it = objects.begin(); objs_it != objects.end(); objs_it++)
		{
			(*objs_it).second.reset();
			//delete (*objs_it).second;
		}
		objects.clear();
	}

	void Init();			//��ʼ��������Ϣ
	void InitKeys();

	void Update(float& dt);			//��Ҫ����ʱ��������־�����ʱ������shader�У�
	void Draw();					//���Ƴ���
private:
};