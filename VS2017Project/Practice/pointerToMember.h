#pragma once
//ָ�룬һ������ָ�������һ������������ȡ�����ָ��Ҳ�ǿ���ָ�����Ա�ģ��������Ա���������Ա������

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

//ָ��ָ�����Ա
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

//��Ա����ָ�룬��ʵ������������У�Ӧ�ú��ٻ�ʹ�õ����������������ͨ���̳кͶ�̬��ʽ�����
typedef void (Widget::*pMem)(int) const;
void testPointToDataFunction()
{
	Widget w;
	Widget *wp = &w;
	//��typedef��ʽ����
	void (Widget::*pmem)(int) const = &Widget::h;
	(w.*pmem)(1);
	(wp->*pmem)(2);

	//ʹ��typedef�ķ�ʽ����
	pMem pmem2 = &Widget::g;
	(w.*pmem2)(1);
	(wp->*pmem2)(2);
}
