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