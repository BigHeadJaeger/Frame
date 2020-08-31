#include "RenderQueue.h"
#include"RenderFrameModel.h"

void RenderQueue::Render(shared_ptr<Object> root)
{
	PerpareQueue(root, transparentMap);

	while (!geometyQueue.empty())
	{
		auto obj = geometyQueue.front();
		if (!obj.expired())
			obj.lock()->Draw();
		geometyQueue.pop();
	}
	// ������Ⱦ͸������
	for (auto it = transparentMap.rbegin(); it != transparentMap.rend(); it++)
	{
		if (!it->second.expired())
			it->second.lock()->Draw();
	}

	transparentMap.clear();
}

void RenderQueue::PerpareQueue(shared_ptr<Object> obj, map<float, weak_ptr<Object>>& tMap)
{
	auto render = obj->GetComponent<MeshRenderer>();
	if (render)
	{
		if (render->material->renderMode == RenderMode::Opaque)
		{
			geometyQueue.push(obj);
		}
		else
		{
			auto eyePos = RenderFrameModel::GetInstance().GetMainCamera()->GetEyePosition();
			float dis = distance(eyePos, obj->transform->position);
			// ��ֹ��������ӵ��ͬ���ľ��벻���ж������һ��ƫ��
			while (!tMap[dis].expired())
				dis += offset;

			tMap[dis] = obj;
		}

	}
	// �ݹ鴦���ӽڵ�
	for (auto it = obj->children.begin(); it != obj->children.end(); it++)
	{
		if (*it)
			PerpareQueue(*it, tMap);
	}
}
