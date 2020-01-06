#pragma once
#include <functional>
#include <iostream>
#include <string>
using namespace std;

//功能和c中的函数指针很像一样，但是更安全，封装的更好
//doubleReferenceTest中解释了右值引用。
std::function<double(string)> ff;

double test1(string str)
{
	return stod(str);
}

auto test2 = [](string str ) { return stod(str); };


class Foo {
public:
	Foo(int num) : num_(num) {}
	void print_add(int i) const { std::cout << num_ + i << '\n'; }
	int num_;
};

void FunctionTest()
{
	ff = test1;
	cout << ff("123.33") << endl;

	ff = test2;
	cout<< ff("321.33")<<endl;

	std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
	const Foo foo(314159);
	f_add_display(foo, 1);
	f_add_display(314159, 1);


}
typedef function<int(int)> fun1;
int printOne(int a)
{
	return a;
}
class class1 
{
public:
	int operator()(int i)
	{
		return i*i;
	}
};
class A
{
public:
	int printOne(int i)
	{
		return i * i*i;
	}
};
void FunctionTest2()
{
	cout << "fun create" << endl;
	vector<fun1> pFun;
	fun1 fun;
	fun = printOne;
	pFun.push_back(fun);
	cout << "assign  int printOne(int) to function" << endl;
	cout<<fun(1)<<endl;
	fun = class1();
	cout << "assign Class::operator() to function" << endl;
	pFun.push_back(fun);
	cout<<fun(2)<<endl;
	A a;
	fun = bind(&A::printOne, a,placeholders::_1);
	cout << "assign class int A::printOne(int) to function" << endl;
	cout << fun(2) << endl;
	pFun.push_back(fun);

	auto funEle = pFun.begin();
	cout << "itrator fun" << endl;
	while (funEle != pFun.end())
	{
		cout << (*funEle)(2) << endl;
		funEle++;
	}

}


void ProcessValue(int& i) { std::cout << "LValue processed: " << i << std::endl; } 
void ProcessValue(int&& i) { std::cout << "RValue processed: " << i << std::endl; } 
void doubleReferenceTest() { int a = 0; ProcessValue(a);  ProcessValue(std::move(a)); ProcessValue(1); }
