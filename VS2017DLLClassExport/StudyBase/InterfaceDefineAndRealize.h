#pragma once
#include <string>
using std::string;
class Person
{
private:
	string m_StrName;
public:
	Person() :m_StrName("###") {};
	virtual ~Person() {};
	virtual void Eat() = 0;
	virtual void Sleep() = 0;
	virtual void SetName(const string strName) = 0;
	virtual string GetName() = 0;
	virtual void Work() = 0;
};


class Student :public Person
{
private:
	string m_strName;
public:
	Student() :m_strName("***")
	{};
	~Student() {};
	void Eat();
	void Sleep();
	void SetName(const string strName);
	string GetName();
	void Work();
};

