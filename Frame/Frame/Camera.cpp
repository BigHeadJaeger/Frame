#include "Camera.h"
#include"Object.h"

Camera::Camera()
{
	up = vec3(0.0, 1.0, 0.0);
	lookLeft = vec3(-1.0, 0.0, 0.0);
	lookAtPoint = vec3(0.0, 0.0, 0.0);
	lookDir = vec3(0.0f, 0.0f, -1.0f);
	view = mat4(0);
	pro = mat4(0);
	cameraSpeed = 2;
	fov = 45.f;
	type = COMPONENT_CAMERA;
}

void Camera::Init(vec3 point)
{
	auto pos = object->GetTransform()->position;
	lookAtPoint = point;
	lookDir = normalize(lookAtPoint - pos);

	//计算up
	lookLeft = cross(vec3(0.0, 1.0, 0.0), lookDir);
	up = cross(lookDir, lookLeft);
}

void Camera::SetView()
{
	//lookAtPoint用eyepos加上lookDir即可
	view = lookAt(object->GetTransform()->position, lookAtPoint, up);
	//view *= rotate(mat4(1.0f), 45.0f, vec3(0.0, 1.0, 0.0));
}

void Camera::SetPro()
{
	pro = perspective(radians(fov), ((float)WIDTH) / (HEIGHT), 0.1f, 200.0f);
}

void Camera::SetOrtho(float left, float right, float bottom, float up, float near, float far)
{
	pro = ortho(left, right, bottom, up, near, far);
}

vec3& Camera::GetEyePosition()
{
	return object->GetTransform()->position;
}
