#include "ObjectManager.h"
#include"Object.h"

shared_ptr<Object> ObjectManager::GridObject(float width, float height, int m, int n)
{
	shared_ptr<Object> grid = make_shared<Object>();
	grid->SetName("grid" + to_string(gridCount));
	gridCount++;
	grid->AddComponent<Transform>();
	auto gridMR = grid->AddComponent<MeshReference>();
	gridMR->CreateGrid(width, height, m, n);
	auto gridMRE = grid->AddComponent<MeshRenderer>();
	gridMRE->material = MaterialManager::GetInstance().GetMaterial("DefaultSpecular");
	return grid;
}

shared_ptr<Object> ObjectManager::BoxObject(float width, float height, float depth)
{
	shared_ptr<Object> box = make_shared<Object>();
	box->SetName("box" + to_string(boxCount));
	boxCount++;
	box->AddComponent<Transform>();
	auto meshReference = box->AddComponent<MeshReference>();
	meshReference->CreateBox(width, height, depth);
	auto bR = box->AddComponent<MeshRenderer>();
	bR->material = MaterialManager::GetInstance().GetMaterial("DefaultSpecular");
	return box;
}

shared_ptr<Object> ObjectManager::SphereObject(float radius, int slice, int stack)
{
	shared_ptr<Object> sphere = make_shared<Object>();
	sphere->SetName("sphere" + to_string(sphereCount));
	sphereCount++;
	sphere->AddComponent<Transform>();
	auto meshReference = sphere->AddComponent<MeshReference>();
	meshReference->CreateSphere(radius, slice, stack);
	auto bR = sphere->AddComponent<MeshRenderer>();
	bR->material = MaterialManager::GetInstance().GetMaterial("DefaultSpecular");
	return sphere;
}
