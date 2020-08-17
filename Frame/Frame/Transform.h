//object���������������
#pragma once
#include<glm.hpp>
#include<vector>
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

	void UpdateMatrix()
	{
		world = translate(mat4(1.0), position);
		world = scale(world, scaler);
		if (rotation.x != 0)
			world = rotate(world, rotation.x, vec3(1.0, 0.0, 0.0));
		if (rotation.y != 0)
			world = rotate(world, rotation.y, vec3(0.0, 1.0, 0.0));
		if (rotation.z != 0)
			world = rotate(world, rotation.z, vec3(0.0, 0.0, 1.0));
		worldInvTranspose = transpose(inverse(world));
		auto mainCamera = RenderFrameModel::GetInstance().GetMainCamera();
		worldViewProj = mainCamera->pro * mainCamera->view * world;
	}

	void Update(float dt) override
	{
		if (!isUseable())
			return;
		UpdateMatrix();
	}
};