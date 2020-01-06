#pragma once
//指针，一般用于指向类对象、一般变量、函数等。但是指针也是可以指向类成员的，包括类成员变量和类成员函数。

#include <iostream>
using namespace std;

class Data {
public:
	int a, b, c;
	void print() const {
		cout << "a = " << a << ",b = " << b
			<< ", c=" << c << endl;
	}
};

//指针指向类成员
void testDataMember()
{
	Data d, *dp = &d;
	int Data::*pmInt = &Data::a;
	dp->*pmInt = 47;
	pmInt = &Data::b;
	d.*pmInt = 48;
	pmInt = &Data::c;
	dp->*pmInt = 49;
	dp->print();
}

class Widget {
public:
	void f(int) const {
		cout << "Widget f" << endl;
	}
	void g(int) const {
		cout << "Widget g" << endl;
	}
	void h(int) const {
		cout << "Widget h" << endl;
	}
	void i(int) const {
		cout << "Widget i" << endl;
	}
};

//成员函数指针，其实在面向对象编程中，应该很少会使用到这种情况，都可以通过继承和多态方式解决。
typedef void (Widget::*pMem)(int) const;
void testPointToDataFunction()
{
	Widget w;
	Widget *wp = &w;
	//非typedef方式定义
	void (Widget::*pmem)(int) const = &Widget::h;
	(w.*pmem)(1);
	(wp->*pmem)(2);

	//使用typedef的方式定义
	pMem pmem2 = &Widget::g;
	(w.*pmem2)(1);
	(wp->*pmem2)(2);
}
