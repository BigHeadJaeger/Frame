//object���������������
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
	//�������������
	vec3 position;					//�����λ��
	vec3 scaler;					//����ķŴ�ϵ��
	vec3 rotation;					//�������ת

	//�������������
	mat4x4 world;					//�������
	mat4x4 worldViewProj;			//��������ת������
	mat4x4 worldInvTranspose;		//������������ת��������ռ�
private:


public:
	//���캯��
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

	// �ݹ鸸�ڵ������������
	vec3 RecursionGetWorldPos(shared_ptr<Object> obj, vec3& pos);

	void UpdateMatrix();

	void Update(float dt) override
	{
		if (!isUseable())
			return;
		UpdateMatrix();
	}
};