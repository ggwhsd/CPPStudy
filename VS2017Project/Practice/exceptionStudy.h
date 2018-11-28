#pragma once
#include <iostream>
using namespace std;

void testTryException()
{
	
	int input = -1;
	try
	{
		cout << "enter  -1:" << endl;
		cin >> input;
		cin.get();
		int *num = new int[input];
		delete num;
	}
	catch (...)
	{
		cout << "exception is catched" << endl;
	}
}