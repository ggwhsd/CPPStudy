#include "./stack.h"
#include <string>
template <typename T>
void Stack<T>::Push(T val)
{
	mStack.push_back(val);
}

template<typename T>
T Stack<T>::Pop()
{
	if (IsEmpty())
		return T();
	T val = mStack.back();
	mStack.pop_back();
	return val;
}

template <typename T>
bool Stack<T>::IsEmpty() const
{
	return mStack.empty();
}

//显式模板实例化,否则无法使用，因为模板必须要由定义才能使用。
template class Stack<int>;
template class Stack<double>;
template class Stack<std::string>;
