#include "Transform.h"
#include"Object.h"

void Transform::MoveByDir(vec3 dir, float distant)
{
	position += distant * dir;
}

void Transform::MoveByVector(vec3 displacement)
{
	position += displacement;
}

void Transform::SetPosition(vec3& _position)
{
	position = _position;
}

void Transform::SetPosition(vec3&& _position)
{
	position = _position;
}

void Transform::RotateByAxis(vec3 axis, float angle)
{
	rotation += angle * axis;
}

void Transform::SetRotation(vec3 _rotation)
{
	rotation = _rotation;
}

void Transform::SetScaler(vec3 _scaler)
{
	scaler = _scaler;
}

vec3 Transform::RecursionGetWorldPos(shared_ptr<Object> obj, vec3& pos)
{
	pos += obj->transform->position;
	if (obj->parent.expired())
		return pos;
	else
		return RecursionGetWorldPos(obj->parent.lock(), pos);
}

void Transform::UpdateMatrix()
{
	world = translate(mat4(1.0), position);
	world = scale(world, scaler);
	if (rotation.x != 0)
		world = rotate(world, rotation.x * (float)PI / 180.f, vec3(1.0, 0.0, 0.0));
	if (rotation.y != 0)
		world = rotate(world, rotation.y * (float)PI / 180.f, vec3(0.0, 1.0, 0.0));
	if (rotation.z != 0)
		world = rotate(world, rotation.z * (float)PI / 180.f, vec3(0.0, 0.0, 1.0));

	// 每次矩阵更新的时候要乘 一直向上到根节点的世界矩阵
	auto parent = object.lock()->parent;
	while (!parent.expired())
	{
		world = parent.lock()->transform->world * world;
		parent = parent.lock()->parent;
	}

	//worldInvTranspose = mat4(mat3(transpose(inverse(world))));
	worldInvTranspose = transpose(inverse(world));
	auto mainCamera = RenderFrameModel::GetInstance().GetMainCamera();
	worldViewProj = mainCamera->pro * mainCamera->view * world;
}
