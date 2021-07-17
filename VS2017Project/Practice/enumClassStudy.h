#pragma once
#include <string>
//enum class 相对于 enum 更加精确
//枚举类型变量不再能转换位数字
//且不同枚举变量之间不能比较。
//
enum class enum_A: char {
	eA1,
	eA2,
	eA3
};

enum class enum_B {
	eA1,
	eA2,
	eA3
};


void testEnumClass()
{
	enum_A a = enum_A::eA1;
	enum_B b = enum_B::eA1;
	//std::cout << (a == b) << std::endl;   //error: 不能比较
	//a = 0;     //error: 不能转换

}
