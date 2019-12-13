#pragma once
#ifndef STACK_PRIV_H
#define STACK_PRIV_H

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

#endif