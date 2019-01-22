#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>

using namespace std;

void testCout()
{
	int number = 9;
	cout << setfill('0') << setw(2) << number << endl;
	cout << setfill('0') << setw(2) << setiosflags(ios::left) << number<< endl;
	cout << setfill('0') << setiosflags(ios::right) <<setw(2) << number << endl;
}