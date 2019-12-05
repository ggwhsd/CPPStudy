#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>

using namespace std;

//map ����ģ��ڲ��ṹ�����
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
	void insert2()
	{
		cout << "����������¼" << endl;
		/*�������ظ������ظ���ֱ�Ӹ���*/
		messages.insert(pair<int, string>(++NO, "Tom1"));
		messages.insert(pair<int, string>(NO, "Tom2"));
		messages.insert(pair<int, string>(NO, "Tom3"));
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
	void SameInsertTest()
	{
		insert2();
		display();
		clear();

	}
	
};

//unordered_map ����ģ��ڲ��ṹ��ϣ��

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

//���ȶ���,ʹ�û�������
class STLPriorityQueueTest {
public:
	STLPriorityQueueTest() {
		
	}
	~STLPriorityQueueTest() {}
	priority_queue<int> BigPriority;   // ��ͬ�� priority_queue<int, vector<int>, less<int> > a;  ������������ǰ�棬���ȷ���
	priority_queue<int, vector<int>, greater<int> > SmallPriority;  //С����

	priority_queue<string> BigPriority_String;

	void insertData()
	{
		for (int i = 0; i < 100; i++)
		{
			BigPriority.push(i);
			SmallPriority.push(i);
		}
		BigPriority_String.push("Tom");
		BigPriority_String.push("Jerry");
		BigPriority_String.push("DDDD");
	}
	void Display()
	{
		while (BigPriority.empty() != true)
		{
			
			std::cout << BigPriority.top()<<" ";
			BigPriority.pop();
		}
		std::cout << std::endl;
		while (SmallPriority.empty() != true)
		{

			std::cout << SmallPriority.top() << " ";
			SmallPriority.pop();
		}
		std::cout << std::endl;

		while (BigPriority_String.empty() != true)
		{

			std::cout << BigPriority_String.top() << " ";
			BigPriority_String.pop();
		}
		std::cout << std::endl;

	}
	void test()
	{
		insertData();
		Display();

	}


};

//���ȶ���,ʹ��pair���ͣ��ȽϹ����ȱȽϵ�һ����������ٱȽϵڶ���
class STLPriorityQueueTest2 {
public:
	STLPriorityQueueTest2() {

	}
	~STLPriorityQueueTest2() {}
	priority_queue<pair<int,int> > BigPriority;   // ��ͬ�� priority_queue<int, vector<int>, less<int> > a;  ������������ǰ�棬���ȷ���
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int> > > SmallPriority;  //С����
	priority_queue<pair<string, int> > BigPriority_String;

	void insertData()
	{
		for (int i = 0; i < 100; i++)
		{
			BigPriority.push(pair<int,int>(100-i,i));
			SmallPriority.push(pair<int, int>(100 - i, i));
		}
		BigPriority_String.push(pair<string,int>("Tom",1));
		BigPriority_String.push(pair<string, int>("Jerry",2));
		BigPriority_String.push(pair<string, int>("Jerry",3));
	}
	void Display()
	{
		while (BigPriority.empty() != true)
		{

			std::cout << BigPriority.top().first << "-"<< BigPriority.top().second << " ";
			BigPriority.pop();
		}
		std::cout << std::endl;
		while (SmallPriority.empty() != true)
		{

			std::cout << SmallPriority.top().first<<"-"<< SmallPriority.top().second << " ";
			SmallPriority.pop();
		}
		std::cout << std::endl;

		while (BigPriority_String.empty() != true)
		{

			std::cout << BigPriority_String.top().first<<"-"<<BigPriority_String.top().second << " ";
			BigPriority_String.pop();
		}
		std::cout << std::endl;

	}
	void test()
	{
		insertData();
		Display();

	}


};



//���ȶ���,ʹ���Զ�������,Ĭ��ʹ���Զ������͵�С�ڲ�����
class STLPriorityQueueTest3 {
	struct compare1
	{
		int x;
		compare1(int a) { x = a; }
		bool operator<(const compare1& a) const
		{
			return x < a.x;
		}

	};

	struct compare2
	{
		bool operator()(compare1 a, compare1 b)
		{
			return a.x > b.x;
		}
	};

public:
	STLPriorityQueueTest3() {

	}
	~STLPriorityQueueTest3() {}
	priority_queue<compare1> BigPriority;
	priority_queue<compare1, vector<compare1>, compare2 > BigPriority_comp;

	void insertData()
	{

			BigPriority.push(compare1(3));
			BigPriority.push(compare1(4));
			BigPriority.push(compare1(1));

			BigPriority_comp.push(compare1(3));
			BigPriority_comp.push(compare1(4));
			BigPriority_comp.push(compare1(1));
		
	}
	void Display()
	{
		while (BigPriority.empty() != true)
		{

			std::cout << BigPriority.top().x << " ";
			BigPriority.pop();
		}
		std::cout << std::endl;
		
		while (BigPriority_comp.empty() != true)
		{

			std::cout << BigPriority_comp.top().x << " ";
			BigPriority_comp.pop();
		}
		std::cout << std::endl;



	}
	void test()
	{
		insertData();
		Display();

	}


};

void pairCoutF(pair<string, string> p)
{
	cout << __FUNCTION__ << " "<< p.first << " " << p.second << endl;
}
struct pairCout
{
	void operator()(pair<string, string> p)
	{
		cout << __FUNCTION__ << " " << p.first << " " << p.second << endl;
	}
};
class STLPairStudy
{
public:

public:
	void testPair()
	{
		pair<string, string> pair1{ "key1","1" };
		vector<pair<string, string>> vecPair;
		vecPair.push_back(pair1);
		vecPair.push_back(make_pair("key2", "2"));
		for_each(vecPair.begin(), vecPair.end(), pairCoutF);
		for_each(vecPair.begin(), vecPair.end(), pairCout()); //�Ƽ����ַ�ʽ
	
	}
};