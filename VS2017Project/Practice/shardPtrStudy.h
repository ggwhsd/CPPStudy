#pragma once
#include <iostream>
#include <string>
using namespace std;

void testSharedPtr()
{
	std::shared_ptr<string> pw(new string());
	*pw = "123";
	cout << "pw=" << *pw << endl;
}

void testAutoPtr()
{
	std::auto_ptr<string> pw(new string());
	*pw = "123";
	cout << "pw=" << *pw << endl;
	std::auto_ptr<string> pw2;
	pw2 = pw;
	if (pw.get() == NULL)
		cout << "after pw2 = pw , pw is null, pw2 ="<< *pw2 << endl;

}


void testSharedPtr2()
{
	shared_ptr<string> p1;
	if (!p1)
		cout << "p1==NULL" << endl;

	shared_ptr<string> p2(new string);
	if (p2&&p2->empty()) {
		*p2 = "helloworld";
		cout << *p2 << endl;
	}

	shared_ptr<string> pint(new string("normal usage!"));
	cout << *pint << endl;

	shared_ptr<string> pint1 = make_shared<string>("safe usage!");
	cout << *pint1 << endl;

	shared_ptr<string> pint2 = pint;
	cout << *pint2 << endl;
	cout << *pint << endl;
}