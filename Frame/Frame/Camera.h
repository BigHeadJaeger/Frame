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
	//相机空间的三个向量
	vec3 lookDir;
	vec3 lookLeft;

	float cameraSpeed;

	float isMainCamera = false;
public:
	Camera();
	void Init(vec3 point);
	void SetView();
	void SetPro();																				//设置透视投影矩阵
	void SetOrtho(float left, float right, float bottom, float up, float near, float far);	//设置正交投影矩阵
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
		// 计算视角矩阵
		SetView();
		// 计算投影矩阵
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
	//获取眼睛看向的方向
	GetEyePosition() += lookDir * vec3(dis);		//lookDir决定当前前后走动时对三个轴的贡献，与dis相乘加到eyepos上
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
	auto dist = length(lookAtPoint - GetEyePosition());					//保留LookAt点到镜头的距离
	mat4 ro = rotate(mat4(1.0f), distance, vec3(0.0, 1.0f, 0.0));

	lookDir = (ro * vec4(lookDir, 1.0f));

	lookDir = normalize(lookDir);

	lookAtPoint = lookDir * dist;						//用保留的LookAt点更新

	//更新左方向和上方向
	lookLeft = cross(vec3(0.0, 1.0, 0.0), lookDir);
	up = cross(lookDir, lookLeft);
}

template<typename D>
inline void Camera::UDRotate(D&& dis)
{
	auto dist = length(lookAtPoint - GetEyePosition());
	auto ro = rotate(mat4(1.0f), static_cast<float>(dis), lookLeft);

	lookDir = (ro * vec4(lookDir, 1.0f));
	lookAtPoint = lookDir * dist;						//用保留的LookAt点更新

	//更新左方向和上方向
	lookLeft = cross(vec3(0.0, 1.0, 0.0), lookDir);
	up = cross(lookDir, lookLeft);
}
