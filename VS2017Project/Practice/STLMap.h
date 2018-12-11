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
		cout << "插入三条记录" << endl;
		messages.insert(pair<int,string>(++NO,"Tom1"));
		messages.insert(pair<int, string>(++NO, "Tom2"));
		messages.insert(pair<int, string>(++NO, "Tom3"));
	}
	void display()
	{
		cout << "显示所有记录" << endl;
		for (iter = messages.begin(); iter != messages.end(); ++iter)
		{
			cout << iter->first << '\t' << iter->second << endl;
		}
		cout << "显示size:" << messages.size() << endl;
		cout << "显示包含1的个数count:" << messages.count(1) << endl;
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