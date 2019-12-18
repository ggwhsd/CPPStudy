#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


void ostreamTest(ostringstream &ostr)
{
	ostr;
	ostr.str("");
	ostr << "asdf" << __FUNCTION__ << "cccccccccccccccccccccccccccc" << endl;
	//string gstr = ostr.str();
	cout << "str:" << ostr.str() << endl;
	cout << "c_str:" << ostr.str().c_str() << endl;
	ostr.str("");
	ostr << "asdf" << __FUNCTION__ << "DDDDD" << endl;
	cout << "str:" << ostr.str() << endl;
	cout << "c_str:" << ostr.str().c_str() << endl;
	//ostr.clear();
	ostr.str("");
	
}

void ostreamTest1(ostringstream &ostr)
{
	ostreamTest(ostr);
}


void ostreamTest()
{
	ostringstream ostr;
	int i = 0;

	while (i<10)
	{
		ostreamTest1(ostr);
		i++;
	}

}

namespace streamStudy {
	class TT
	{
	public :
		int i = 0;
	};
	//自定义类似cout的类，实现重载<<
	class MyOutstream

	{

	public:

		const MyOutstream& operator << (int value)const;//对整型变量的重载运算符

		const MyOutstream& operator << (const char*str)const;//对字符串型的重载运算符

	

	};

	const MyOutstream& MyOutstream::operator<<(int value)const
	{

		printf("%d", value);

		return*this;//注意这个返回……

	}

	const MyOutstream& MyOutstream::operator << (const char* str)const

	{

		printf("%s", str);

		return*this;//同样，这里也留意一下……

	}

	void Testfstream()
	{
		MyOutstream myout;
		int i = 100;
		const char *str = "hello world";
		myout << i << str;
	}


	class Myostringstream : public ostringstream
	{
		
	};

	//继承字符流，可以直接使用字符流的的功能
	void TestStream2()
	{
		Myostringstream *my = new Myostringstream();
		(*my)<< "ddd"<<2;
		cout << "str:" << my->str() << endl;
		
	}


	void TestStream3()
	{
		ifstream f;
		f.open("C:\\Users\\a\\Desktop\\GUGW\\swigwin-3.0.12\\Makefile.in");
		string str;
		while (!f.eof())
		{
			f >> str;
			cout << str;
		}
	}


}