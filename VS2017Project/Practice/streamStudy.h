#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


void ostreamTest()
{
	ostringstream ostr;
	ostr << "asdf" << __FUNCTION__ << "ddd" << 1;
	string gstr = ostr.str();
	cout << gstr;
	
}