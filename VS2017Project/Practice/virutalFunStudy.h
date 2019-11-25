#pragma once
#include <iostream>
#include <iomanip>
using namespace std;
//�麯����ķ���,https://www.oschina.net/question/565065_138936
namespace VirtualTable {
	class Base {
	public:
		int i = 0;
	public:

		virtual void f() { cout << "Base::f" << endl; }

		virtual void g() { cout << "Base::g" << endl; }

		virtual void h() { cout << "Base::h" << endl; }

	};

	//��Щ����ʹ�õġ�
	void testVirtualTable()
	{
		
		Base b;

		cout << "�麯����ĵ�ַ\t"  << &b << "\t" << (int*)&b << endl;  //�����������ͬ��
		cout << "�麯����ĵ�һ��ָ��\t" <<*(int*)&b <<"\t" << (int*)*(int*)&b << endl;  //���������ͬ����һ����ʮ���ƣ��ڶ�����ʮ������
		cout << "�麯����ĵڶ���ָ��\t" << (int*)*(int*)&b+1  << endl;  //���������ͬ����һ����ʮ���ƣ��ڶ�����ʮ������	
	}

	class Derive1 :public virtual Base
	{
	public:
		int i = 1;
	public:

		virtual void f() { cout << "Derive1::f" << endl; }

	};
	//�����
	class Derive2 :public virtual Base
	{
	public:
		int i = 2;
	public:

		virtual void f() { cout << "Derive2::f" << endl; }
		virtual void g() { cout << "Derive2::g" << endl; }
	};

	class Derive3 :public virtual Base
	{
	public:
		int i = 3;
	public:
		virtual void f() { cout << "Derive3::f" << endl; }

		virtual void g() { cout << "Derive3::g" << endl; }

		virtual void h() { cout << "Derive3::h" << endl; }
	};

	class Derive4 :public  Derive2, public  Derive3
	{
	public:
		int i = 4;
	public:
		virtual void f() { cout << "Derive4::f" << endl; }

		virtual void g() { cout << "Derive4::g" << endl; }

		virtual void h() { cout << "Derive4::h" << endl; }
	};
	class AbstractBase
	{
	public:
		int i = 0;
	public:

		virtual void f() = 0;

		virtual void g() = 0;

		virtual void h() = 0;
	};

	class AbstractDerive1 : public AbstractBase
	{
	public:
		int i = 1;
	public:

		virtual void f()  { cout << "AbstractDerive1::f" << endl; };

		virtual void g() { cout << "AbstractDerive1::g" << endl; };

		virtual void h() = 0;
	};

	class AbstractDerive2 : public AbstractDerive1
	{
	public:
		int i = 2;
	public:

		virtual void f() { cout << "AbstractDerive2::f" << endl; };

		virtual void g() { cout << "AbstractDerive2::g" << endl; };

		virtual void h() { cout << "AbstractDerive2::h" << endl; };
	};

	void TestDisplay(Base *base,string title)
	{
		cout << title  << "\t"<<base->i << endl;
		base->f();
		base->g();
		base->h();
	}

	void TestDerived()
	{
		Base *base = nullptr;
		cout << "sizeof int" << sizeof(int) << endl;
		Derive1* d1 = new Derive1();
		TestDisplay(d1,"Derived1");
		cout << "��С�ֽ���"<<sizeof(*d1) << endl;
		Derive2* d2 = new Derive2();
		TestDisplay(d2,"Derived2");
		cout << "��С�ֽ���" << sizeof(*d2) << endl;
		Derive3* d3 = new Derive3();
		TestDisplay(d3,"Derived3");
		cout << "��С�ֽ���" << sizeof(*d3) << endl;
		Derive4* d4 = new Derive4();
		TestDisplay(d4, "Derived4");
		cout << "��С�ֽ���" << sizeof(*d4) << endl;
		cout<<d4->i;


	}

	void TestAbstractDerived()
	{
		AbstractBase* base = nullptr;
		AbstractDerive2 *d2 = new AbstractDerive2();
		cout << "����̳���Ĵ�С�ֽ���" <<sizeof(*d2) << endl;

		base = d2;
		base->h();

	}
}


