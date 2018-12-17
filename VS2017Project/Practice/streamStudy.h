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
	cout << "1" << ostr.str() << endl;;
	ostr.clear();
	cout << "2"<< ostr.str() << endl;;
	ostr.str("");
	cout << "3" << ostr.str() << endl;;
	//下面是比较特殊的
	ostr.str("ggggg");
	ostr << "ffffff" << endl;
	cout << "4" << ostr.str() << endl;;
	


	
}


