#include "ObjectManager.h"
#include"Object.h"

shared_ptr<Object> ObjectManager::GridObject(float width, float height, int m, int n)
{
	shared_ptr<Object> grid = make_shared<Object>();
	grid->SetName("grid" + gridCount);
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
	box->SetName("box" + boxCount);
	boxCount++;
	box->AddComponent<Transform>();
	auto meshReference = box->AddComponent<MeshReference>();
	meshReference->CreateBox(width, height, depth);
	auto bR = box->AddComponent<MeshRenderer>();
	bR->material = MaterialManager::GetInstance().GetMaterial("DefaultSpecular");
	return box;
}
