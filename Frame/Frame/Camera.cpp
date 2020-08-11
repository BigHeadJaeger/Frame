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
	fov = 45.f;
	type = COMPONENTTYPE::COMPONENT_CAMERA;
}

void Camera::SetView()
{
	//lookDir = normalize(lookAtPoint - eyePos);
	//lookAtPoint��eyepos����lookDir����
	view = lookAt(eyePos, lookAtPoint, up);
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
