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

//鼠标的状态和信息
struct Mouse
{
	vec2 cursorPrePos;			//记录光标的前一位置
	vec2 cursorNowPos;			//记录现在的位置
	bool mouseLeftDown;
	bool mouseRightDown;

	bool isSelect;				//表示当前有已经选择的东西
	bool isCatchPoint;			//表示当前正在拖动顶点

	int catchObjIndex;			//当前拖动的物体的index



	Mouse() :cursorPrePos(vec2(0, 0)), mouseLeftDown(false), mouseRightDown(false)
	{
		isCatchPoint = false;
		isSelect = false;
	}
};

// 因为glfw只有按下和弹起两个键盘事件，因此重写可支持持续按键的键盘按键事件
class Key
{
public:
	KEYNAME keyName;
	//bool isDown;
	// 类似函数指针作用的模板，可以接受普通函数以及lambda函数
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


	//此函数在update中不断执行传进来的function
	void Execute()
	{
		if (eventFunctionPtr != NULL)
		{
			eventFunctionPtr();
		}
	}

	//指定key执行down事件，并且指定一个需要外部函数
	// eventFunctionPtr指向按键类型不同的处理方式，比如按下、弹起、持续。outerFunction指定按下这个按钮之后具体在外部要进行的逻辑，eventFunctionPtr和outerFunction都是先将处理记录下来不立即处理，处理时间为下一帧最开始的update中，所以是一个异步的操作
	template<typename F>
	void BindDownEvent(F f)
	{
		eventFunctionPtr = [&]() {
			// 按钮按下只需要执行一次，执行完了之后解除绑定
			outerFunction();
			UnBind();
		};
		outerFunction = f;
	}

	template<typename F>
	void BindKeepEvent(F f)
	{
		eventFunctionPtr = [&]() {
			// 不断执行，不进行解绑
			outerFunction();
		};
		outerFunction = f;
	}

	template<typename F>
	void BindUpEvent(F f)
	{
		eventFunctionPtr = [&]() {
			// 按钮按下只需要执行一次，执行完了之后解除绑定
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


