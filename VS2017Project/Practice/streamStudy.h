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
	//�Զ�������cout���࣬ʵ������<<
	class MyOutstream

	{

	public:

		const MyOutstream& operator << (int value)const;//�����ͱ��������������

		const MyOutstream& operator << (const char*str)const;//���ַ����͵����������

	

	};

	const MyOutstream& MyOutstream::operator<<(int value)const
	{

		printf("%d", value);

		return*this;//ע��������ء���

	}

	const MyOutstream& MyOutstream::operator << (const char* str)const

	{

		printf("%s", str);

		return*this;//ͬ��������Ҳ����һ�¡���

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

	//�̳��ַ���������ֱ��ʹ���ַ����ĵĹ���
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