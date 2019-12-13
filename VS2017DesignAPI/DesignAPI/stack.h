#pragma once
#ifndef STACK_H
#define STACK_H

#include <vector>
template <typename T>
class Stack
{
public:
	void Push(T val);
	T Pop();
	bool IsEmpty() const;

private:
	std::vector<T> mStack;

};
//将实现和声明分别放在两个头文件中的技术。特别适合模板开发。叫做隐式实例化API设计。
//#include "./stack_priv.h"

//显式实例化的情况下，用于提供给客户的声明。显示实例化在Stack.cpp文件的末尾。
typedef Stack<int> IntStack;
typedef Stack<double> DoubleStack;
typedef Stack<std::string> StringStack;
#endif
