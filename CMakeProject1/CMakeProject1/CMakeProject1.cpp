// CMakeProject1.cpp: 定义应用程序的入口点。
//

#include "CMakeProject1.h"
#include "../myLibOne/myLibOne.h"
#include "../myLibTwo/myLibTwo.h"
#include <iostream>
#include <thread>



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
	cout << "Hello CMake." << endl;
	cout<< "StaticLib call : " <<staticLibMethod(3, 5) << endl;
	cout << "DynimacLib call : " << DynamicLibMethod(3, 5) << endl;
	return 0;
}
