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
//��ʵ�ֺ������ֱ��������ͷ�ļ��еļ������ر��ʺ�ģ�忪����������ʽʵ����API��ơ�
//#include "./stack_priv.h"

//��ʽʵ����������£������ṩ���ͻ�����������ʾʵ������Stack.cpp�ļ���ĩβ��
typedef Stack<int> IntStack;
typedef Stack<double> DoubleStack;
typedef Stack<std::string> StringStack;
#endif
