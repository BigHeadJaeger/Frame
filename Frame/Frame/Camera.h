#pragma once
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
//#include<initializer_list>
using namespace glm;
class Camera
{
public:
	vec3 eyePos;
	vec3 lookAtPoint;
	vec3 up;
	mat4 view;
	mat4 pro;
	//����ռ����������
	vec3 lookDir;
	vec3 lookLeft;

	float cameraSpeed;
public:
	Camera();
	template<typename V>
	void Init(V&& pos, V&& point);
	//void Init(vec3& pos, vec3& point);
	//void Init(vec3&& pos, vec3&& point);
	void SetView();
	void SetPro();																				//����͸��ͶӰ����
	void SetOrtho(float left, float right, float bottom, float up, float near, float far);	//��������ͶӰ����
public:
	template<typename D>
	void Walk(D&& dis);
	template<typename D>
	void LRMove(D&& dis);
	template<typename D>
	void LRRotate(D&& dis);
	template<typename D>
	void UDRotate(D&& dis);
};

//Camera* Camera::MainCamera = NULL;

class MainCamera :public Camera
{
private:
	MainCamera(){}
public:
	static MainCamera& GetInstance()
	{
		static MainCamera instacne;
		return instacne;
	}

	MainCamera(MainCamera&) = delete;
};

template<typename V>
inline void Camera::Init(V&& pos, V&& point)
{
	eyePos = pos;
	lookAtPoint = point;
	lookDir = normalize(lookAtPoint - eyePos);

	//����up
	lookLeft = cross(vec3(0.0, 1.0, 0.0), lookDir);
	up = cross(lookDir, lookLeft);
}

template<typename D>
inline void Camera::Walk(D&& dis)
{
	//��ȡ�۾�����ķ���
	//lookDir = normalize(lookAtPoint - eyePos);
	eyePos += lookDir * vec3(dis);		//lookDir������ǰǰ���߶�ʱ��������Ĺ��ף���dis��˼ӵ�eyepos��
	lookAtPoint += lookDir * vec3(dis);
}

template<typename D>
inline void Camera::LRMove(D&& dis)
{
	eyePos += lookLeft * vec3(dis);
	lookAtPoint += lookLeft * vec3(dis);
}

template<typename D>
inline void Camera::LRRotate(D&& dis)
{
	auto distance = static_cast<float>(dis);
	auto dist = length(lookAtPoint - eyePos);					//����LookAt�㵽��ͷ�ľ���
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
	auto dist = length(lookAtPoint - eyePos);
	auto ro = rotate(mat4(1.0f), static_cast<float>(dis), lookLeft);

	lookDir = (ro * vec4(lookDir, 1.0f));
	lookAtPoint = lookDir * dist;						//�ñ�����LookAt�����

	//����������Ϸ���
	lookLeft = cross(vec3(0.0, 1.0, 0.0), lookDir);
	up = cross(lookDir, lookLeft);
}
