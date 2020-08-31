// ��������������г����������Ⱦ˳��
#pragma once
#include<string>
#include<iostream>
#include<queue>
#include"Object.h"

class RenderQueue
{
private:
	float offset = 0.0000001;
public:
	queue<weak_ptr<Object>> geometyQueue;
	// �������������map����������͸�������˳��
	map<float, weak_ptr<Object>> transparentMap;
public:
	void Render(shared_ptr<Object> root);
private:
	// �Ӹ��ڵ㴦��ÿһ��object������Ӧ�Ķ�����
	void PerpareQueue(shared_ptr<Object> obj, map<float, weak_ptr<Object>>& tMap);

};