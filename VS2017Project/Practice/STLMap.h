#pragma once
#include <map>
#include <string>
#include <iostream>

using namespace std;

class STLMapTest {
	map<int, string> messages;
	map<int, string>::iterator iter;
	int NO;
public:
	STLMapTest():NO(0) {
		
	}
	~STLMapTest() {}
	void insert()
	{
		cout << "����������¼" << endl;
		messages.insert(pair<int,string>(++NO,"Tom1"));
		messages.insert(pair<int, string>(++NO, "Tom2"));
		messages.insert(pair<int, string>(++NO, "Tom3"));
	}
	void display()
	{
		cout << "��ʾ���м�¼" << endl;
		for (iter = messages.begin(); iter != messages.end(); ++iter)
		{
			cout << iter->first << '\t' << iter->second << endl;
		}
		cout << "��ʾsize:" << messages.size() << endl;
		cout << "��ʾ����1�ĸ���count:" << messages.count(1) << endl;
	}
	void clear()
	{
		messages.clear();
		if (messages.empty() == true)
			cout << "no data in the map\n";
	}
	void baseFuctionTest()
	{
	
		insert();
		display();
		clear();
	}
	
};