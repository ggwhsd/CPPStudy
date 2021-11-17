// CMakeProject1.cpp: 定义应用程序的入口点。
//

#include "CMakeProject1.h"
#include "../myLibOne/myLibOne.h"
#include "../myLibTwo/myLibTwo.h"
#include "../myLibOne/log.h"
#include "./v.h"
#include <iostream>
#include <thread>

//该log方法为头文件实现，在引用的dll和lib库中均有include，所以，此处不能用include，只能前置声明。
//void log(std::string);

using namespace std;

void func()
{
	cout << "fff" << endl;
}
void TestThreadLib()
{
	thread t(func);
	t.join();
}

int main()
{

	log(__FUNCTION__);
	cout << "Hello CMake." << endl;
	v();
	cout<< "StaticLib call : " <<staticLibMethod(3, 5) << endl;
	cout << "DynimacLib call : " << DynamicLibMethod(3, 5) << endl;
	return 0;
}
