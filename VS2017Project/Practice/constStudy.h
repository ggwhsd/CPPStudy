#pragma once
#include <iostream>
using namespace std;

const int constantValue = 100;

void testModifyConst()
{
	//constantValue = 90;   //会提示错误，不可修改的左值
}

int ChangeValue = 100;
/* const放在函数后面，只能是成员函数，不能是c函数
void testModifyAppendConst() const
{

}*/
class ConstTest
{
	mutable int changeValue2 = 111;
	int ChangeValue = 99;
public:
	void testModifyAppendConst() const
	{
		//ChangeValue = 33;  //会提示错误，不可修改的左值
		::ChangeValue = 33;  //用的全局变量，const函数只负责类范围的成员变量。且不负责mutable修饰的变量
		changeValue2 = 33;  
	}
	int getConstValue() const
	{
		return ChangeValue;
	}
	void SetConstParameter(const ConstTest & value)
	{
		int v = value.getConstValue();
		ChangeValue = value.getConstValue() + 1;
	}

	const ConstTest getClone()
	{
		return *this;
	}

};


void ConstTestF()
{
	ConstTest ct;
	cout << "获取尾部有const函数值："<< ct.getConstValue() << endl;
	ConstTest ct2;
	ct2.SetConstParameter(ct);
	cout << "ct1.ChangeValue" << ct.getConstValue() <<" ptr "<<&ct << endl;
	cout << "ct2.ChangeValue" << ct2.getConstValue() << " ptr " << &ct2 << endl;
	ConstTest ct3 = ct2.getClone();
	cout << "ct3.ChangeValue" << ct3.getConstValue() << " ptr " << &ct3 << endl;

	//额外了解，地址分布
	int a;
	int b;
	int c;
	cout << "int bytes "<< sizeof a << endl;
	cout << &a << endl;
	cout << &b << endl;
	cout << &c << endl;
	int d[3];
	cout << &d[0] << endl;
	cout << &d[1] << endl;
	cout << &d[2] << endl;
}
