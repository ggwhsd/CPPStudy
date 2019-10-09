#pragma once
#include <iostream>
using namespace std;

const int constantValue = 100;

void testModifyConst()
{
	//constantValue = 90;   //����ʾ���󣬲����޸ĵ���ֵ
}

int ChangeValue = 100;
/* const���ں������棬ֻ���ǳ�Ա������������c����
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
		//ChangeValue = 33;  //����ʾ���󣬲����޸ĵ���ֵ
		::ChangeValue = 33;  //�õ�ȫ�ֱ�����const����ֻ�����෶Χ�ĳ�Ա�������Ҳ�����mutable���εı���
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
	cout << "��ȡβ����const����ֵ��"<< ct.getConstValue() << endl;
	ConstTest ct2;
	ct2.SetConstParameter(ct);
	cout << "ct1.ChangeValue" << ct.getConstValue() <<" ptr "<<&ct << endl;
	cout << "ct2.ChangeValue" << ct2.getConstValue() << " ptr " << &ct2 << endl;
	ConstTest ct3 = ct2.getClone();
	cout << "ct3.ChangeValue" << ct3.getConstValue() << " ptr " << &ct3 << endl;

	//�����˽⣬��ַ�ֲ�
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
