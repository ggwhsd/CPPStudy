#pragma once
#include <iostream>
#include <string>
using namespace std;

class PlaceNew
{
public :
	PlaceNew()
	{
		cout << __FUNCTION__ << endl;
	}
	PlaceNew(int a,int b) :v1(a),v2(b)
	{
		cout << __FUNCTION__ << "-"<< a<<"-"<<b<< endl;
		s1 = "hello";
	}
	~PlaceNew()
	{
		cout << __FUNCTION__ << "-" << v1 << "-" << v2 << endl;
	}
	int GetValue()
	{
		return v1 + v2;
	}
	string GetS1()
	{
		return s1;
	}

private:
	int v1;
	int v2; //即使调用了析构函数，该基础类型值在内存中还是存在的。
	string s1;  //类类型在上述析构函数之后就为空字符串
};

// 以下例子，就可以看出，placement可以在已经分配好的内存上直接创建对象。我觉得和线程池的本质原理都是内存的如何复用，前者是从语言标准中提供的功能，后者是基于语言之上开发的功能。
void TestPlacementNew()
{
	char *ptr_memory = new char[1024]{ 0 };

	PlaceNew *pNormalNew1 = new PlaceNew(1,1);
	cout << "pNormalNew1 getvalue=" << pNormalNew1->GetValue() << endl << endl;
	delete pNormalNew1;

	PlaceNew *pPlaceNew1 = new (ptr_memory) PlaceNew(1, 2);
	cout << "Address = " << pPlaceNew1 <<endl;;
	cout << "pPlaceNew1 getvalue = " << pPlaceNew1->GetValue() << endl;
	cout << "pPlaceNew1 getS1 = " << pPlaceNew1->GetS1() << endl;
	pPlaceNew1->~PlaceNew();
	cout << "after ~PlaceNew()" << endl;
	cout << "pPlaceNew1 getvalue = " << pPlaceNew1->GetValue() << endl;
	cout << "pPlaceNew1 getS1 = " << pPlaceNew1->GetS1() << endl << endl;;

	PlaceNew *pPlaceNew2 = new (ptr_memory) PlaceNew(1, 2);
	cout << "Address = " << pPlaceNew2 << endl;;
	cout << "pPlaceNew2 getvalue = " << pPlaceNew2->GetValue() << endl;;
	

	cout << "Sizeof PlaceNew = " << sizeof(PlaceNew) << endl;
	//因为<<对字符串指针直接输出字符串的值，而不是指针的值。所以如果需要输出字符串的地址，通过将其转为int指针，就可以显示地址了，
	cout << "Address PlaceNew + 1= " << (int *)(ptr_memory + sizeof(PlaceNew)) << endl;
	
	PlaceNew *pPlaceNew3 = new (pPlaceNew2 +1) PlaceNew(1, 2);
	cout << "Address (new (pPlaceNew2 +1))= " << pPlaceNew3 << endl;;
	cout << "pPlaceNew2 getvalue = " << pPlaceNew3->GetValue() << endl;;
	pPlaceNew3->~PlaceNew();
	cout << "after ~PlaceNew()" << endl;
	cout << "pPlaceNew2 getvalue = " << pPlaceNew3->GetValue() << endl;;

}