#pragma once
#include<cstdarg>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
void fun(const char* format, ...) {
	char info[400] = { 0 };//��ȷ��info���Է���ת�����ַ�
	va_list args;
	va_start(args, format);
	vsprintf_s(info, format, args);
	va_end(args);
	std::string s(info);
	if (sizeof(info) <= s.size()) {
		assert("parameter too long");
	}
	std::cout << s << '\n';
}

void fun(int count, ...) {
	char info[400] = { 0 };//��ȷ��info���Է���ת�����ַ�
	va_list args;
	va_start(args, count);
	int CountSum = 0;
	for (int i = 0; i < count; ++i)
	{
		CountSum += va_arg(args, int);
	}

	va_end(args);

	cout << CountSum << endl;

}

void testMultiParam()
{
	fun("[%s] [%d] [%f]\n", "789012", 34, 67.89);
	fun(5, 1, 23, 4, 5, 6);
}