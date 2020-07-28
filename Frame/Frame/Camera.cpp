#include "Camera.h"

Camera::Camera()
{
	up = vec3(0.0, 1.0, 0.0);
	lookLeft = vec3(-1.0, 0.0, 0.0);
	lookAtPoint = vec3(0.0, 0.0, 0.0);
	lookDir = vec3(0.0f, 0.0f, -1.0f);
	eyePos = vec3(0.0, 0.0, 0.0);
	view = mat4(0);
	pro = mat4(0);
	cameraSpeed = 2;
}

void Camera::SetView()
{
	//lookDir = normalize(lookAtPoint - eyePos);
	//lookAtPoint用eyepos加上lookDir即可
	view = lookAt(eyePos, lookAtPoint, up);
	//view *= rotate(mat4(1.0f), 45.0f, vec3(0.0, 1.0, 0.0));
}

void Camera::SetPro()
{
	pro = perspective(45.0f, ((float)1200) / (1000), 0.1f, 1000.0f);
}

void Camera::SetOrtho(float left, float right, float bottom, float up, float near, float far)
{
	pro = ortho(left, right, bottom, up, near, far);
}


MainCamera* MainCamera::instance = NULL;