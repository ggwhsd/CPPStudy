#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

void testTryException()
{
	
	int input = -1;
	try
	{
		cout << "enter  -1:" << endl;
		cin >> input;
		cin.get();
		int *num = new int[input];
		delete num;
	}
	catch (...)
	{
		cout << "exception is catched" << endl;
	}
}

class X
{
public :
	class Trouble {};
	class Small : public Trouble {};
	class Big :public Trouble {};
	void f() { throw Big(); }
};

void testTryThrowException()
{
	X x;
	try
	{
		x.f();
	}
	/*
	   �������ǻᲶ�񵽻����У������ʹ�õ������࣬��ôӦ�ý���������쳣����ŵ���ǰ��
	*/
	catch (X::Small&)
	{
		cout << "Small" << endl;
	}
	catch (X::Big&)
	{
		cout << "Big" << endl;
	}
	catch (X::Trouble&)
	{
		cout << "Trouble" << endl;
	}
}

class MyError :public runtime_error {
public:
	MyError(const string & msg = "") :runtime_error(msg) {}

};

void testMyErrorException()
{
	try {
		throw MyError("my message exception");
	}
	catch (MyError &x)
	{
		cout<<x.what();
	}
}