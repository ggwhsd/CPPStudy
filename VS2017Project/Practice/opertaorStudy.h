#pragma once
#include <iostream>
#include <string>
using namespace std;

class Date
{
private:
	int day, month, year;
	string dateInString;
public:
	Date(int inMonth, int inDay, int inYear):month(inMonth),day(inDay),year(inYear)
	{};
	Date& operator ++ () {
		++day;
		return *this;
	}
	Date& operator -- () {
		--day;
		return *this;
	}
	void DisplayDate()
	{
		cout << month << " / " << day << " / " << year << endl;

	}
	//��׺
	Date operator ++ (int) {
		Date copy(month, day, year);
		++day;
		return copy;
	}
	Date operator -- (int) {
		Date copy(month, day, year);
		--day;
		return copy;
	}
	//ת�������
	operator const char*()
	{
		ostringstream formattedDate;
		formattedDate << month << " / " << day << " / " << year;
		dateInString = formattedDate.str();
		return dateInString.c_str();
	}

	//˫Ŀ����� + 
	Date operator + (int daysToadd)
	{
		Date newDate(month, day + daysToadd, year);
		return newDate;
	}
	Date operator - (int daysToadd)
	{
		Date newDate(month, day - daysToadd, year);
		return newDate;
	}


	//˫Ŀ����� +=
	void operator += (int daysToadd)
	{
		day += daysToadd;

	}
	void operator -= (int daysToadd)
	{
		day -= daysToadd;
	}
	//���ص��ںͲ�����
	bool operator == (const const Date& compareTo)
	{
		return ((day == compareTo.day)
			&& (month == compareTo.month)
			&& (year == compareTo.year));

	}
	bool operator != (const const Date& compareTo)
	{
		return !(this->operator==(compareTo));

	}
	//����С�ڡ�����
	bool operator<(const Date& compareTo)
	{
		if (year < compareTo.year)
			return true;
		else if (month < compareTo.month)
			return true;
		else if (day < compareTo.day)
			return true;
		else
			return false;
	}
	bool operator<=(const Date& compareTo)
	{
		if (year <= compareTo.year)
			return true;
		else if (month <= compareTo.month)
			return true;
		else if (day <= compareTo.day)
			return true;
		else
			return false;
	}
	bool operator>(const Date& compareTo)
	{
		if (year > compareTo.year)
			return true;
		else if (month > compareTo.month)
			return true;
		else if (day > compareTo.day)
			return true;
		else
			return false;
	}
	bool operator>=(const Date& compareTo)
	{
		if (year >= compareTo.year)
			return true;
		else if (month >= compareTo.month)
			return true;
		else if (day >= compareTo.day)
			return true;
		else
			return false;
	}

	//���ظ�ֵ�����
	Date& operator=(const Date&cpy)
	{
		month = cpy.month;
		year = cpy.year;
		day = cpy.day;
		return *this;
	}
	//�����±�
	const int& operator[] (int index) const
	{
		switch (index)
		{
		case 0:
			return day;
			break;
		case 1:
			return month;
			break;
		case 2:
			return year;
			break;
		default:
			break;
		}
	}
	//�����������ӵ�к���������������Ҳ�к�������functor
	void operator()(string input) const
	{
		cout << input << endl;
	}
};

void testOperatorPrefix()
{
	Date holiday(12, 18, 2019);
	holiday.DisplayDate();
	++holiday;
	holiday.DisplayDate();
	--holiday;
	holiday.DisplayDate();
	return;
}

void testOperatorPostfix()
{
	Date holiday(12, 18, 2019);
	holiday.DisplayDate();
	holiday++;
	holiday.DisplayDate();
	holiday--;
	holiday.DisplayDate();
	return;
}

void testOperatorCharPtr()
{
	Date holiday(12, 18, 2019);
	cout << holiday << endl;
}


void testOperatorTwoParameters()
{
	cout << __FUNCTION__ << endl;
	Date holiday(12, 18, 2019);
	holiday.DisplayDate();
	holiday = holiday + 1;
	holiday.DisplayDate();
	holiday = holiday - 1;
	holiday.DisplayDate();

	holiday += 10;
	holiday.DisplayDate();
	holiday -= 10;
	holiday.DisplayDate();

	Date holiday2(12, 17, 2019);
	if (holiday == holiday2)
	{
		cout << "yes" << endl;
	}
	else
	{
		cout << "no" << endl;
	}

	if (holiday > holiday2)
	{
		cout << ">" << endl;
	}
	else
	{
		cout << "<=" << endl;
	}

	Date holiay3(12,20,2019);
	holiday2 = holiay3 = holiday;
	holiay3.DisplayDate();
	return;
}

void testOperatorindex()
{
	cout << __FUNCTION__ << endl;
	Date holiday(12, 18, 2019);
	cout << holiday[1] << " / " << holiday[0] << " / " << holiday[2] << "  " << endl;
}

void testOperatorFunctor()
{
	Date holiday(18, 12, 2019);
	holiday("i am a functor");

}

