// 用来管理最后所有场景物体的渲染顺序
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
	// 物体距离和物体的map，用来保存透明物体的顺序
	map<float, weak_ptr<Object>> transparentMap;
public:
	void Render(shared_ptr<Object> root);
private:
	// 从根节点处理每一个object放入相应的队列中
	void PerpareQueue(shared_ptr<Object> obj, map<float, weak_ptr<Object>>& tMap);

};