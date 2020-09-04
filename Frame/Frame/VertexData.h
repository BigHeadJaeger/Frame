#pragma once
//#include<GL/glew.h>
#include<glad/glad.h>
#include<glm.hpp>
#include<vector>
#include<map>
using namespace std;
using namespace glm;

enum StateType
{
	STATE_TYPE_POSITION,
	STATE_TYPE_NORMAL,
	STATE_TYPE_TEXCOORD,
	STATE_TYPE_COLOR,
};

struct StateInfo
{
	bool isEnable;
	GLint location;
	StateInfo()
	{
		isEnable = false;
		location = -1;
	}

	//StateInfo(bool )

};

class VertexData
{
public:
	//物体的VAO、VBO编号
	GLuint VAO;
	GLuint VBO;
	GLuint IndexBuffer;

	GLint drawType;					//顶点buffer的绘制方式
	//GLint drawUnitNumber;			//绘制单元的数量

	vector<vec3> position;
	vector<vec3> normal;
	vector<vec2> texcoord;
	vector<vec4> color;

	map<StateType, StateInfo> propertyState;

	size_t totalVertex;

public:
	VertexData()
	{
		propertyState.insert(pair<StateType, StateInfo>(STATE_TYPE_POSITION, StateInfo()));
		propertyState.insert(pair<StateType, StateInfo>(STATE_TYPE_NORMAL, StateInfo()));
		propertyState.insert(pair<StateType, StateInfo>(STATE_TYPE_TEXCOORD, StateInfo()));
		propertyState.insert(pair<StateType, StateInfo>(STATE_TYPE_COLOR, StateInfo()));
		totalVertex = 0;
		drawType = GL_TRIANGLES;
	}

	void setState(StateType _type, bool _state) { propertyState[_type].isEnable = _state; }
	void setLocation(StateType _type, GLint num) { propertyState[_type].location = num; }

	bool getState(StateType _type) { return propertyState[_type].isEnable; }
	GLint getLocation(StateType _type) { return propertyState[_type].location; }

	void initMemory(size_t& numOfVertex)
	{
		position.reserve(numOfVertex);
		normal.reserve(numOfVertex);
		texcoord.reserve(numOfVertex);
		color.reserve(numOfVertex);
	}

	void Clear()
	{
		totalVertex = 0;
		position.clear();
		normal.clear();
		texcoord.clear();
		color.clear();
		propertyState.clear();
	}
};