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


