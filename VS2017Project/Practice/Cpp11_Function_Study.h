#pragma once
#include <functional>
#include <iostream>
#include <string>
using namespace std;

//功能和c中的函数指针很像一样，但是更安全，封装的更好
std::function<double(string)> ff;

double test1(string str)
{
	return stod(str);
}

auto test2 = [](string str ) { return stod(str); };


void FunctionTest()
{
	ff = test1;
	cout << ff("123.33") << endl;

	ff = test2;
	cout<< ff("321.33")<<endl;



}



void ProcessValue(int& i) { std::cout << "LValue processed: " << i << std::endl; } 
void ProcessValue(int&& i) { std::cout << "RValue processed: " << i << std::endl; } 
void doubleReferenceTest() { int a = 0; ProcessValue(a);  ProcessValue(std::move(a)); ProcessValue(1); }
