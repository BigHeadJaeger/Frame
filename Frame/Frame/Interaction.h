#pragma once
#include<functional>
#include<glm.hpp>
using namespace glm;
using namespace std;

enum KEYNAME
{
	BTNW,
	BTNA,
	BTNS,
	BTND,
	BTN1,
	BTN2,
	BTN3,
	BTN4,
	BTNC,
	NONE,
};

//����״̬����Ϣ
struct Mouse
{
	vec2 cursorPrePos;			//��¼����ǰһλ��
	vec2 cursorNowPos;			//��¼���ڵ�λ��
	bool mouseLeftDown;
	bool mouseRightDown;

	bool isSelect;				//��ʾ��ǰ���Ѿ�ѡ��Ķ���
	bool isCatchPoint;			//��ʾ��ǰ�����϶�����

	int catchObjIndex;			//��ǰ�϶��������index



	Mouse() :cursorPrePos(vec2(0, 0)), mouseLeftDown(false), mouseRightDown(false)
	{
		isCatchPoint = false;
		isSelect = false;
	}
};

// ��Ϊglfwֻ�а��º͵������������¼��������д��֧�ֳ��������ļ��̰����¼�
class Key
{
public:
	KEYNAME keyName;
	//bool isDown;
	// ���ƺ���ָ�����õ�ģ�壬���Խ�����ͨ�����Լ�lambda����
	function<void()> eventFunctionPtr;
	function<void()> outerFunction;
private:

public:
	Key()
	{
		keyName = NONE;
		eventFunctionPtr = nullptr;
		outerFunction = nullptr;
	}
	Key(KEYNAME name)
	{
		keyName = name;
		eventFunctionPtr = nullptr;
		outerFunction = nullptr;
	}


	//�˺�����update�в���ִ�д�������function
	void Execute()
	{
		if (eventFunctionPtr != NULL)
		{
			eventFunctionPtr();
		}
	}

	//ָ��keyִ��down�¼�������ָ��һ����Ҫ�ⲿ����
	// eventFunctionPtrָ�򰴼����Ͳ�ͬ�Ĵ���ʽ�����簴�¡����𡢳�����outerFunctionָ�����������ť֮��������ⲿҪ���е��߼���eventFunctionPtr��outerFunction�����Ƚ������¼������������������ʱ��Ϊ��һ֡�ʼ��update�У�������һ���첽�Ĳ���
	template<typename F>
	void BindDownEvent(F f)
	{
		eventFunctionPtr = [&]() {
			// ��ť����ֻ��Ҫִ��һ�Σ�ִ������֮������
			outerFunction();
			UnBind();
		};
		outerFunction = f;
	}

	template<typename F>
	void BindKeepEvent(F f)
	{
		eventFunctionPtr = [&]() {
			// ����ִ�У������н��
			outerFunction();
		};
		outerFunction = f;
	}

	template<typename F>
	void BindUpEvent(F f)
	{
		eventFunctionPtr = [&]() {
			// ��ť����ֻ��Ҫִ��һ�Σ�ִ������֮������
			outerFunction();
			UnBind();
		};
		outerFunction = f;
	}

	void UnBind()
	{
		eventFunctionPtr = nullptr;
		outerFunction = nullptr;
	}

	
};


