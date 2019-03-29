#include "stdafx.h"
#include "./InterfaceDefineAndRealize.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;


void Student::Eat()
{
	cout << "student sleep." << endl;
}

void Student::Sleep()
{
	cout << "student eat." << endl;
}

void Student::SetName(const string strName)
{
	m_strName = strName;
}

string Student::GetName()
{
	return m_strName;
}

void Student::Work()
{
	cout << "student work" << endl;
}
