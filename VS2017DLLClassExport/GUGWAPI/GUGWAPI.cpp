// GUGWAPI.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "a.h"
#include <iostream>
using namespace std;
// This is the constructor of a class that has been exported.
// see NaiveApproach.h for the class definition
CNaiveApproach::CNaiveApproach(int i) : m_iwuyg(i)
{
}

void CNaiveApproach::Func()
{
	wcout << L" cswuyg test dll , i = " << m_iwuyg << endl;
	system("pause");
}

void CBase::Test()
{
	wcout << L"Just a  Test" << endl;
	system("pause");
}

void CDate::Test2()
{
	wcout << L"Test 2" << endl;
	system("pause");
}

