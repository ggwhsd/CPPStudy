#pragma once
#include <string>
//enum class ����� enum ���Ӿ�ȷ
//ö�����ͱ���������ת��λ����
//�Ҳ�ͬö�ٱ���֮�䲻�ܱȽϡ�
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
	//std::cout << (a == b) << std::endl;   //error: ���ܱȽ�
	//a = 0;     //error: ����ת��

}
