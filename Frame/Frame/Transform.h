//object的坐标相关属性类
#pragma once
#include<glm.hpp>
#include<vector>
#include<list>
using namespace glm;
#include"Component.h"
#include"ShaderDataTool.h"
#include"RenderFrameModel.h"
#include"Camera.h"

class Transform : public Component
{
public:
	//物体的坐标属性
	vec3 position;					//物体的位置
	vec3 scaler;					//物体的放大系数
	vec3 rotation;					//物体的旋转

	//物体的坐标属性
	mat4x4 world;					//世界矩阵
	mat4x4 worldViewProj;			//最终坐标转换矩阵
	mat4x4 worldInvTranspose;		//用来将法向量转换到世界空间
private:


public:
	//构造函数
	Transform(vec3 _pos = vec3(0), vec3 _scaler = vec3(1.0), vec3 _rotation = vec3(0)) :position(_pos), scaler(_scaler), rotation(_rotation)
	{
		type = COMPONENT_TRANSFORM;
	}

	void MoveByDir(vec3 dir, float distant);
	void MoveByVector(vec3 displacement);
	void SetPosition(vec3& _position);
	void SetPosition(vec3&& _position);

	void RotateByAxis(vec3 axis, float angle);
	void SetRotation(vec3 _rotation);
	
	void SetScaler(vec3 _scaler);

	// 递归父节点计算世界坐标
	vec3 RecursionGetWorldPos(shared_ptr<Object> obj, vec3& pos);

	void UpdateMatrix();

	void Update(float dt) override
	{
		if (!isUseable())
			return;
		UpdateMatrix();
	}
};