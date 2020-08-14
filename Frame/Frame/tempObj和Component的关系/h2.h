#pragma once
#include"h1.h"

class Object
{
public:
	shared_ptr<Component> testA;
	string asd;

public:
	Object()
	{
		asd = "sadasd";
		//dynamic_pointer_cast
		testA = make_shared<Component>();
		testA->testB = this;
	}


	void fun1()
	{
		cout << testA->testB->asd << endl;
	}
};