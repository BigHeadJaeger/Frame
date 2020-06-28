#pragma once
#include<GL/glew.h>
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
	vector<vec3> position;
	vector<vec3> normal;
	vector<vec2> texcoord;
	vector<vec4> color;
	map<StateType, StateInfo> propertyState;

	GLuint totalVertex;

public:
	VertexData()
	{
		propertyState.insert(pair<StateType, StateInfo>(STATE_TYPE_POSITION, StateInfo()));
		propertyState.insert(pair<StateType, StateInfo>(STATE_TYPE_NORMAL, StateInfo()));
		propertyState.insert(pair<StateType, StateInfo>(STATE_TYPE_TEXCOORD, StateInfo()));
		propertyState.insert(pair<StateType, StateInfo>(STATE_TYPE_COLOR, StateInfo()));
		totalVertex = 0;
	}

	void setState(StateType _type, bool _state) { propertyState[_type].isEnable = _state; }
	void setLocation(StateType _type, GLint num) { propertyState[_type].location = num; }

	bool getState(StateType _type) { return propertyState[_type].isEnable; }
	GLint getLocation(StateType _type) { return propertyState[_type].location; }
};