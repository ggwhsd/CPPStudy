#pragma once
#ifndef MEDIATOR_H
#define MEDIATOR_H
#include <iostream>
#include <list>
#include <string>
using namespace std;
class Country;
class UnitedNations
{
public:
	virtual void Declare(string message, Country *colleague) = 0;

};
class Country
{
protected:
	UnitedNations * mediator;
public:
	Country() {}
	Country(UnitedNations *m) :mediator(m) {}
	virtual void Declare(string m) = 0;
	virtual void GetMessage(string  st) = 0;
};
class USA :public Country
{
public:
	USA(UnitedNations *m) { mediator = m; }
	void Declare(string m)
	{
		mediator->Declare(m, this);
	}
	void GetMessage(string m)
	{
		cout << "美国获得对方信息： " << m << endl;
	}
};
class Iraq :public Country
{
public:
	Iraq(UnitedNations* m) { mediator = m; }
	void Declare(string m)
	{
		mediator->Declare(m, this);
	}
	void GetMessage(string m)
	{
		cout << "伊拉克获得对方信息： " << m << endl;
	}
};

class UnitedNationsSecurityCouncil :public UnitedNations
{

	list<Country*> colleagues;
public:
	void AddColleague(Country * c) { colleagues.push_back(c); }
	void Declare(string message, Country *colleague)
	{
		for(list<Country*>::iterator it= colleagues.begin() ; it!= colleagues.end(); it++)
		{
			if (colleague != *it)
				(*it)->GetMessage(message);
		}
	}

};
#endif