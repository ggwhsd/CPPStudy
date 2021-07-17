#pragma once
#include <type_traits>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

template<class T>
auto isParamSpecialType(T t)  -> std::enable_if_t<std::is_same<int,std::remove_cv_t<T>>::value,int>
{
	cout << "ParamSpecial is int" << endl;
}

template<class T>
auto isParamSpecialType(T t)  -> std::enable_if_t<std::is_same<double, std::remove_cv_t<T>>::value, double>
{
	cout << "ParamSpecial is double" << endl;
}


void testTraits()
{
	isParamSpecialType(1.1);
	isParamSpecialType(1);

	
}
