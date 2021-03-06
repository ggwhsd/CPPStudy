// Dll1.cpp: 定义 DLL 应用程序的导出函数。
// 不使用def文件的dll导出方式

#include "stdafx.h"
#include "first.h"  

#include <iostream>  
using namespace std;


//   0 = 黑色      8 = 灰色
//   1 = 蓝色      9 = 淡蓝色
//   2 = 绿色      A = 淡绿色
//   3 = 浅绿色    B = 淡浅绿色
//   4 = 红色      C = 淡红色
//   5 = 紫色      D = 淡紫色
//   6 = 黄色      E = 淡黄色
//   7 = 白色      F = 亮白色

//   控制台前景颜色
enum ConsoleForegroundColor
{
	enmCFC_Red = FOREGROUND_INTENSITY | FOREGROUND_RED,
	enmCFC_Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	enmCFC_Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	enmCFC_Yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	enmCFC_Purple = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	enmCFC_Cyan = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	enmCFC_Gray = FOREGROUND_INTENSITY,     
	enmCFC_White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	enmCFC_HighWhite = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	enmCFC_Black = 0,
};

enum ConsoleBackGroundColor
{
	enmCBC_Red = BACKGROUND_INTENSITY | BACKGROUND_RED,
	enmCBC_Green = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
	enmCBC_Blue = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
	enmCBC_Yellow = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
	enmCBC_Purple = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
	enmCBC_Cyan = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
	enmCBC_White = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	enmCBC_HighWhite = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	enmCBC_Black = 0,
};

/*void show(void)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	cout << "                    加";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "油";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << ",";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "给";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	cout << "自";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	cout << "己" <<endl;
}*/

void clear()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleForegroundColor::enmCFC_White | ConsoleBackGroundColor::enmCBC_Black);
}

void SetConsoleStrIn_Blue_White()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleForegroundColor::enmCFC_Blue | ConsoleBackGroundColor::enmCBC_White);
}

void showStrIn_Blue(char * str)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleForegroundColor::enmCFC_Blue | ConsoleBackGroundColor::enmCBC_White);
	cout <<str;
	clear();
}

void SetConsoleStrIn_Red_Yello()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleForegroundColor::enmCFC_Red | ConsoleBackGroundColor::enmCBC_Yellow);
}

void SetConsoleDefault()
{
	clear();
}

void showStrIn_Red_Yello(char * str)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleForegroundColor::enmCFC_Red | ConsoleBackGroundColor::enmCBC_Yellow);
	cout << str;
	clear();
}


/*int panny(int i, int(*call_back)(int a, int b))
{
	int aa;
	aa = i * i;
	call_back(i, aa);
	return 0;
}
*/

