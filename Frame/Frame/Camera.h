#pragma once
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include"Const.h"
#include"Component.h"
#include"ShaderDataTool.h"
//#include<initializer_list>
using namespace glm;
class Camera : public Component
{
public:
	float fov;
	vec3 lookAtPoint;
	vec3 up;
	mat4 view;
	mat4 pro;
	//����ռ����������
	vec3 lookDir;
	vec3 lookLeft;

	float cameraSpeed;

	float isMainCamera = false;
public:
	Camera();
	void Init(vec3 point);
	void SetView();
	void SetPro();																				//����͸��ͶӰ����
	void SetOrtho(float left, float right, float bottom, float up, float near, float far);	//��������ͶӰ����
	template<typename D>
	void Walk(D&& dis);
	template<typename D>
	void LRMove(D&& dis);
	template<typename D>
	void LRRotate(D&& dis);
	template<typename D>
	void UDRotate(D&& dis);
public:
	void Update(float dt) override
	{
		if (!isUseable())
			return;
		// �����ӽǾ���
		SetView();
		// ����ͶӰ����
		SetPro();
	}

	void SetMain()
	{
		isMainCamera = true;
	}

	vec3& GetEyePosition();
};

template<typename D>
inline void Camera::Walk(D&& dis)
{
	//��ȡ�۾�����ķ���
	GetEyePosition() += lookDir * vec3(dis);		//lookDir������ǰǰ���߶�ʱ��������Ĺ��ף���dis��˼ӵ�eyepos��
	lookAtPoint += lookDir * vec3(dis);
}

template<typename D>
inline void Camera::LRMove(D&& dis)
{
	GetEyePosition() += lookLeft * vec3(dis);
	lookAtPoint += lookLeft * vec3(dis);
}

template<typename D>
inline void Camera::LRRotate(D&& dis)
{
	auto distance = static_cast<float>(dis);
	auto dist = length(lookAtPoint - GetEyePosition());					//����LookAt�㵽��ͷ�ľ���
	mat4 ro = rotate(mat4(1.0f), distance, vec3(0.0, 1.0f, 0.0));

	lookDir = (ro * vec4(lookDir, 1.0f));

	lookDir = normalize(lookDir);

	lookAtPoint = lookDir * dist;						//�ñ�����LookAt�����

	//����������Ϸ���
	lookLeft = cross(vec3(0.0, 1.0, 0.0), lookDir);
	up = cross(lookDir, lookLeft);
}

template<typename D>
inline void Camera::UDRotate(D&& dis)
{
	auto dist = length(lookAtPoint - GetEyePosition());
	auto ro = rotate(mat4(1.0f), static_cast<float>(dis), lookLeft);

	lookDir = (ro * vec4(lookDir, 1.0f));
	lookAtPoint = lookDir * dist;						//�ñ�����LookAt�����

	//����������Ϸ���
	lookLeft = cross(vec3(0.0, 1.0, 0.0), lookDir);
	up = cross(lookDir, lookLeft);
}
