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

//��ʽģ��ʵ����,�����޷�ʹ�ã���Ϊģ�����Ҫ�ɶ������ʹ�á�
template class Stack<int>;
template class Stack<double>;
template class Stack<std::string>;
