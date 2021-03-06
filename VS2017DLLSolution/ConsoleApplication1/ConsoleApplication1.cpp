// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//	测试使用
#pragma comment(lib,"Dll_feituoguan.lib")
#include "stdafx.h"
#include "first.h"
#include "algo.h"
#include "CMath.h"
#include "CMathChild.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

//TEST

int panny_call_back(int a, int b)
{
	int c;
	c = a + b;
	printf("输出：%d\n", c);
	return 11;
}

int main()
{


	char *str = new char[100];
	strcpy_s(str,6,"hello");
	showStrIn_Blue(str);
	showStrIn_Red_Yello(str);
	SetConsoleStrIn_Blue_White();

	cout << "引用使用模块定义def格式导出的类的dll函数" << endl;
	printf("%f",MAX(9,10));
	std::cout << MIN(100, 101) << endl;
	SetConsoleDefault();

	cout << "访问dll中的默认CMath" << endl;
	InitCMath(nullptr);
	cout << "CMath_Add" << CMath_Add(3, 2) << endl;
	ReleaseCMath();

	cout << "继承CMath" << endl;
	CMath * cc = new CMathChild();

	InitCMath(cc);
	cout << "CMath_Add" << CMath_Add(3, 2) << endl;
	CMath * c2 = new CMath();
	cout << "CMath.Add" << c2->Add(3, 2) << endl;;
	ReleaseCMath();

	cout << "接口封装 隐藏实现的CMath" << endl;
	CMath * c3 = new CMath();
	c3->Init();

	cout << "CMath.Add" << c3->Add(3, 2)<< endl;;
	system("pause");

    return 0;
}

