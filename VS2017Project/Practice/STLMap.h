#pragma once
#include <map>
#include <unordered_map>
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

class STLUnorderedMapTest {
public:
	STLUnorderedMapTest() {
		mp.reserve(2);
	}
	~STLUnorderedMapTest() {}
	unordered_map<string, string> mp;
	void insert(string key, string value)
	{
		mp[key] = value;
	}
	string get(string key)
	{
		return mp[key];
	}
	void test()
	{
		mp["t1"] = "xxxxxxx";
		mp["t2"] = "yyyyyyy";
		mp["t3"] = "zzzzzzz";
		
		cout<<mp.bucket_count()<<endl;
		cout << mp.size()<<endl;
		if (mp.find("t3") != mp.cend())
		{
			cout << mp["t3"] << endl;
			cout << mp["t4"] << endl;
		}
		char name[7] = { 0 };
		name[0] = 't';
		
		int i = 0;
		while (i < 100)
		{
			strcpy(&name[1], to_string(i).c_str());
			mp[name] = "xxxxxx";
			i++;
		}
		cout << mp.bucket_count()<<endl;
		cout << mp.size()<<endl;
	
	}
};