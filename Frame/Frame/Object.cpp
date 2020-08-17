#include "Object.h"

//void Object::Update(float dt)
//{
//
//}

//void Object::SetRenderer(RENDERERTYPE type)
//{
//	switch (type)
//	{
//	case RENDERERTYPE::DEFAULT:
//		renderer = &DefaultRenderer::GetRenderer();
//		shaderData.reset();
//		shaderData = make_shared<DefaultShaderData>();
//		break;
//	case RENDERERTYPE::SIMPLE:
//		//renderer = SimpleRenderer::GetRenderer();
//		////delete shaderData;
//		//shaderData.release();
//		//shaderData = unique_ptr<SimpleShaderData>();
//		//break;
//	case RENDERERTYPE::VERTEXCOLOR:
//		renderer = &VertexColorRender::GetRenderer();
//		//delete shaderData;
//		shaderData.reset();
//		shaderData = make_shared<VertexShaderData>();
//		//shaderData = unique_ptr<VertexShaderData>();
//		break;
//	case RENDERERTYPE::MPS:
//		break;
//	default:
//		break;
//	}
//}

//void Metaball::SetSourcePoints(vec3 firstPos, int w, int h, int d)
//{
//	initPos = firstPos;
//	CubeDistribute(sourcePoints, firstPos, vec3(0.2), w, h, d);
//}
//
//void Metaball::InitBufferData()
//{
//	int pointCount = 0;
//	vector<float> verticesInfo;
//	bool provideNormal;
//	bool provideTex;
//	marchingCube.GetMeshData(sourcePoints, verticesInfo, provideNormal, provideTex);
//	//当ball运动都超出最开始的定的边界时就不会有顶点信息产生
//	if (verticesInfo.size() != 0)
//	{
//		pointCount = verticesInfo.size() / 8;
//		shaderData->drawUnitNumber = pointCount;
//		shaderData->InitVertexBuffer(verticesInfo, provideNormal, provideTex);
//	}
//	//pointCount = verticesInfo.size() / 8;
//	//shaderData->drawUnitNumber = pointCount;
//	//shaderData->InitVertexBuffer(verticesInfo, provideNormal, provideTex);
//}
//
//void Metaball::Update(float dt)
//{
//	cout << 1 / dt << endl;
//	temp += dt;
//	//对sourcePoint进行坐标变化
//	float fOffset = 1.0 + sinf(temp);
//	//cout << fOffset << endl;
//
//	for (int i = 0; i < sourcePoints.size(); i++)
//	{
//		int a = i % 3;
//		switch (a)
//		{
//		case 0:
//			sourcePoints[i].x = initPos.x * fOffset;
//			//cout << sourcePoints[i].x << endl;
//			break;
//		case 1:
//			sourcePoints[i].y = initPos.y * fOffset;
//			break;
//		case 2:
//			sourcePoints[i].z = initPos.z * fOffset;
//			break;
//		default:
//			break;
//		}
//	}
//
//	//每一帧都需要重新初始化顶点buffer
//	//if (test % 2 == 0)
//	//{
//	//	
//	//}
//	InitBufferData();
//	shaderData->UpdateMatrix(transformation);
//}
//
//void Metaball::Draw()
//{
//	renderer->Render(shaderData);
//}
