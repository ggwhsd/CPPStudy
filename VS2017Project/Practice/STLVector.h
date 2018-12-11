#pragma once
#include <vector>
#include <iostream>
#include <chrono>
#include <string>
using namespace std;

struct MyStruct
{
	int a;
	int b;
	string d;
	//used in DisplayContents via cout
	operator const char*() const
	{
		return d.c_str();
	}

};


class STLVectorTest {


public:
	STLVectorTest() {}
	~STLVectorTest() {}

//vector<int>   push_back;begin;end;find;distance;
void testVector()
{
	vector<int> intArray;
	intArray.push_back(50);
	intArray.push_back(2991);
	intArray.push_back(23);
	intArray.push_back(9999);
	cout << "the context:" << endl;
	vector<int>::iterator arrIterator = intArray.begin();
	while (arrIterator != intArray.end())
	{
		cout << *arrIterator << endl;
		++arrIterator;

	}
	vector<int>::iterator elFound = find(intArray.begin(), intArray.end(), 2991);
	if (elFound != intArray.end())
	{
		int elPos = distance(intArray.begin(), elFound);
		cout << "Value" << *elFound;
		cout << "found in the vector at position:" << elPos << endl;

	}
}

//vector<MyStruct>   push_back;begin;end
void testVector2()
{
	vector<MyStruct> myArray;
	int i = 0;
	MyStruct m;
	m.a = 1;
	m.b = 2;
	m.d = "aa";
	while (i<100000)
	{
		myArray.push_back(m);
		i++;
	}
	m.a = 2;
	m.d = "bb";
	myArray.push_back(m);


	vector<MyStruct>::iterator it = myArray.begin();
	cout << it->d << endl;
	while (it != myArray.end())
	{
		if (it->a == 2) {
			cout << it->d << endl;
		}
		++it;
	}
}

//没有使用reserve的方式之后，初始化时间
void testVectorTime1(int out)
{
	vector<MyStruct> tenElement;
	//tenElement.reserve(10);
	cout << "tenElement.size():" << tenElement.size() << endl;
	cout << "tenElement.capacity():" << tenElement.capacity() << endl;
	clock_t start = clock();
	MyStruct s = { 1,1,"a" };
	s.d = "a0";
	tenElement.push_back(s);

	auto it = tenElement.begin();
	cout << it._Ptr << endl;

	int i = 1;
	for (; i < out; i++)
	{
		s.d = "a" + to_string(i);
		tenElement.push_back(s);
	}
	clock_t end = clock();
	cout << "生成tenElement" << out << "个对象 耗时" << end - start << "MILLISECOND" << endl;
	start = clock();
	for (size_t i = 0; i < out; i++)
	{
		if (tenElement[i].a == out)
			break;
	}
	end = clock();
	cout << "生成tenElement" << out << "个对象 耗时" << end - start << "MILLISECOND" << endl;

	it = tenElement.begin();
	cout << it._Ptr << endl;
	tenElement.erase(it);
	//vector<MyStruct>::iterator it = tenElement.begin();

}

//使用reserve的方式之后，初始化时间
void testVectorTime2()
{
	vector<MyStruct> tenElement;
	tenElement.reserve(100000);
	cout << "tenElement.size():" << tenElement.size() << endl;
	cout << "tenElement.capacity():" << tenElement.capacity() << endl;
	clock_t start = clock();
	MyStruct s = { 1,1,"a" };
	int i = 0;
	for (; i < 100000; i++)
	{
		s.a = i;
		tenElement.push_back(s);
	}
	clock_t end = clock();
	cout << "生成tenElement 1000000个对象 耗时" << end - start << "MILLISECOND" << endl;
	start = clock();
	for (size_t i = 99999; i > 0; i--)
	{
		if (tenElement[i].a == 2)
		{
			cout << tenElement[i].a << endl;
			break;
		}
	}
	end = clock();

	cout << "遍历tenElement 1000000个对象 耗时" << end - start << "MILLISECOND" << endl;;

	//vector<MyStruct>::iterator it = tenElement.begin();

}

//erase
void testVectorErase(int out)
{
	vector<MyStruct> tenElement;
	tenElement.reserve(10);
	cout << "tenElement.size():" << tenElement.size() << endl;
	cout << "tenElement.capacity():" << tenElement.capacity() << endl;
	clock_t start = clock();
	MyStruct s = { 1,1,"a" };
	s.d = "a0";
	tenElement.push_back(s);

	auto it = tenElement.begin();
	cout << it._Ptr << endl;

	int i = 1;
	for (; i < out; i++)
	{
		s.d = "a" + to_string(i);
		tenElement.push_back(s);
	}
	clock_t end = clock();
	cout << "生成tenElement" << out << "个对象 耗时" << end - start << "MILLISECOND" << endl;
	start = clock();
	for (size_t i = 0; i < out; i++)
	{
		if (tenElement[i].a == out)
			break;
	}
	end = clock();
	cout << "生成tenElement" << out << "个对象 耗时" << end - start << "MILLISECOND" << endl;

	cout << "before tenElement.erase(tenElement.begin());" << endl;
	it = tenElement.begin();
	cout << it->d <<it._Ptr << endl;

	tenElement.erase(tenElement.begin());
	cout << "after tenElement.erase(tenElement.begin());" << endl;
	it = tenElement.begin();
	cout << it->d << it._Ptr << endl;
	

}


};