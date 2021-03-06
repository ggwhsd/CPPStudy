// STLTest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <string>
#include <set>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <map>

#include "structType.h"

using namespace std;


template <typename T>
void DisplayContents(const T& container)
{
	for (auto element = container.cbegin();
		element != container.cend();
		++element)
	{
		cout << *element << endl;
	}
	cout << endl;
}

template <typename T>
void DisplayMapContents(const T& container)
{
	for (auto element = container.cbegin();
		element != container.cend();
		++element)
	{
		cout << " first="<<element->first << " second="<< element->second << endl;
	}
	cout << endl;
}


void testList3(int count)
{
	list<MyStruct> tenElement;
	cout << "tenElement.size():" << tenElement.size() << endl;
	clock_t start = clock();
	MyStruct s = { 1,1,"a" };
	int i = 0;
	for (; i < count; i++)
	{
		s.d = "a" + to_string(i);
		tenElement.push_back(s);
	}
	clock_t end = clock();
	cout << "生成tenElement "<< count <<"个对象 耗时" << end - start << "MILLISECOND" << endl;;
	start = clock();
	for(list<MyStruct>::iterator stemp = tenElement.begin();stemp != tenElement.end();++stemp)
	{
		if (stemp->a == count)
			break;
	}
	end = clock();
	cout << "遍历tenElement "<< count <<"个对象 耗时" << end - start << "MILLISECOND" << endl;;

	//vector<MyStruct>::iterator it = tenElement.begin();

}

void testString() 
{
	using namespace std;
	const char* c = "Hello string";
	cout << c << endl;
	string strFrom (c);
	string str2Copy (strFrom);
	cout << " " << str2Copy << endl;
	cout << str2Copy[1] << endl;
	strFrom += "aaa";
	cout << strFrom << endl;
	
	transform(strFrom.begin(), strFrom.end(), strFrom.begin(), ::toupper);
	cout << strFrom << endl;


}

template <typename T>
void DisplayDeque(const deque<T>& inDeq) 
{
	for (auto element = inDeq.cbegin();
		element != inDeq.cend();
		++element)
	{
	
		cout << element->a << ' ';
	}
	cout << "size:" <<inDeq.size() <<endl;
}


void testDeque()
{
	deque <MyStruct> strs;
	MyStruct m{ 1,2,"a" };
	strs.push_back(m);
	m.a = 2;
	m.b = 3;
	m.d = "b";
	strs.push_front(m);
	DisplayDeque(strs);

}




void testList()
{
	list <MyStruct> linkInts{ {1, 1,"a"} };
	linkInts.push_back(MyStruct{2,2,"b"});
	linkInts.push_front({3,3,"c"});

	DisplayContents(linkInts);
	auto it = linkInts.begin();
	it->d = "d";
	DisplayContents(linkInts);
}
void testList2()
{
	list <int> linkInts{ -101,42 };
	linkInts.push_back(10);
	linkInts.push_front(2011);
	DisplayContents(linkInts);
	auto it = find(linkInts.cbegin(), linkInts.cend(), -101);
	linkInts.erase(it);
	DisplayContents(linkInts);
}

void testListFind()
{
	list <MyStruct*> linkInts;
	MyStruct m1;
	m1.a = 1;
	m1.b = 1;
	m1.d = 1;
	MyStruct *m2 = new MyStruct();
	m2->a = 2;
	m2->b = 2;
	m2->d = 2;
	cout << &m1 << endl;
	cout << m2 << endl;
	linkInts.push_back(&m1);
	linkInts.push_front(m2);
	DisplayContents(linkInts);
	list<MyStruct*> linkPtr;
	linkPtr = linkInts;
	auto it = find(linkInts.cbegin(), linkInts.cend(), m2);
	linkInts.erase(it);
	DisplayContents(linkInts);
	DisplayContents(linkPtr);


}


void testMapFind()
{
	list <MyStruct*> linkInts;
	MyStruct m1;
	m1.a = 1;
	m1.b = 1;
	m1.d = 1;
	MyStruct *m2 = new MyStruct();
	m2->a = 2;
	m2->b = 2;
	m2->d = 2;
	cout << &m1 << endl;
	cout << m2 << endl;
	linkInts.push_back(&m1);
	linkInts.push_front(m2);
	DisplayContents(linkInts);
	auto it = find(linkInts.cbegin(), linkInts.cend(), m2);
	linkInts.erase(it);
	DisplayContents(linkInts);
}


template <typename T>
struct SortDescending
{
	bool operator()(const T& lhs, const T& rhs) const{
		return lhs > rhs;
	}
};


void testSet() {
	
	set<int, SortDescending<int>> setInts1;
	multiset<int> msetInts1;
	setInts1.insert(-1);
	setInts1.insert(2);
	setInts1.insert(-3);
	set<int> setInts2;
	setInts2.insert(-1);
	setInts2.insert(2);
	setInts2.insert(-3);
	//按照顺序输出
	DisplayContents(setInts1);
	DisplayContents(setInts2);

	if (setInts1.find(-1) != setInts1.cend())
		cout << "FIND" << endl;
	else
		cout << "NO FIND" << endl;
	setInts1.erase(2);
	DisplayContents(setInts1);
}


struct ContactItem
{
	string name;
	string phoneNum;
	string displayAs;

	ContactItem(const string& nameInit, const string & phone)
	{
		name = nameInit;
		phoneNum = phone;
		displayAs = (name + ":" + phoneNum);

	}
	//重载操作符
	//used by set::find()
	bool operator == (const ContactItem & itemToCompare) const
	{
		return (itemToCompare.name == this->name);
	}
	//used to sort
	bool operator < (const ContactItem& itemToCompare) const
	{
		return (this->name < itemToCompare.name);
	}
	//used in DisplayContents via cout
	operator const char*() const
	{
		return displayAs.c_str();
	}
};

string getTime()
{
	time_t now;
	now = time(&now);;
	struct tm vtm;
	localtime_s(&vtm, &now);
	return to_string(vtm.tm_sec);
}

void testSet2()
{
	set<ContactItem> setContacts;
	setContacts.insert(ContactItem("jack1", "+1 7881"));
	setContacts.insert(ContactItem("jack2", "+1 7882"));
	setContacts.insert(ContactItem("jack3", "+1 7883"));
	setContacts.insert(ContactItem("jack4", "+1 7884"));
	setContacts.insert(ContactItem("jack5", "+1 7885"));
	DisplayContents(setContacts);
	cout << "enter the name you wish to delete" << endl;
	string inputname;
	getline(cin, inputname);
	auto contactFound = setContacts.find(ContactItem(inputname, ""));
	if (contactFound != setContacts.end())
	{
		setContacts.erase(contactFound);
	}
	else
	{
		cout << "contact not found" << endl;
	}
	DisplayContents(setContacts);
	return;
}

void thread_task() {
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	cout << "hello thread"  << std::this_thread::get_id()<<endl;
}


void f1(int n)
{
	for (int i = 0; i < 5; ++i) {
		std::cout << "Thread " << n << " executing\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
void f2(int& n)
{
	for (int i = 0; i < 5; ++i) {
		std::cout << "Thread 2 executing\n";
		++n;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void thread_task2(int n) {
	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout << "hello thread "
		<< std::this_thread::get_id()
		<< " paused " << n << " seconds" << std::endl;
}

void testThread()
{
	std::thread threads[5];
	std::cout << "Spawning 5 threads...\n";
	for (int i = 0; i < 5; i++) {
		threads[i] = std::thread(thread_task2, i + 1);
	}
	std::cout << "Done spawning threads! Now wait for them to join\n";
	for (auto& t : threads) {
		t.join();
	}
	std::cout << "All threads joined.\n";
}

mutex g_mutex;
int g_count = 0;
void testThreadMutext()
{
	thread thr1([]() {
		for (int i = 0; i < 5; i++) {
			lock_guard<mutex> lock(g_mutex);    //①
			g_count += 10;
		}
	});
	thread thr2([]() {
		for (int i = 0; i < 5; i++) {
			lock_guard<mutex> lock(g_mutex);    //②
			g_count += 20;
		}
	});
	thr1.join();
	thr2.join();
	cout << g_count << endl;
}


std::atomic<bool> ready(false);    // can be checked without being set
std::atomic_flag winner = ATOMIC_FLAG_INIT;    // always set when checked

void count1m(int id)
{
	while (!ready) {
		std::this_thread::yield();
	} // 等待主线程中设置 ready 为 true.

	for (int i = 0; i < 1000000; ++i) {
	} // 计数.

	if (!winner.test_and_set()) {
		std::cout << "thread #" << id << " won!\n";
	}
};

void testAtomic1()
{
	std::vector<std::thread> threads;
	std::cout << "spawning 10 threads that count to 1 million...\n";
	for (int i = 1; i <= 10; ++i)
		threads.push_back(std::thread(count1m, i));
	ready = true;

	for (thread & th : threads)
		th.join();

}


struct Node { int value; Node* next; };
std::atomic<Node*> list_head(nullptr);

void append(int val)
{
	Node* newNode = new Node{ val, list_head };
	while (!list_head.compare_exchange_weak(newNode->next, newNode)) {}
}

void testAtomic2()
{
	std::vector<std::thread> threads;
	for (int i = 0; i < 10; ++i) threads.push_back(std::thread(append, i));
	for (auto& th : threads) th.join();
	for (Node* it = list_head; it != nullptr; it = it->next)
		std::cout << ' ' << it->value;
	std::cout << '\n';
	Node* it; while (it = list_head) { list_head = it->next; delete it; }
}



class  Foo {
	 Foo(int x, double y);
};


void testBigEnd()
{
	union
	{
		unsigned short i;
		unsigned char a[2];
	}u;
	u.a[0] = 0x27;
	u.a[1] = 0x8a;

	cout << u.i << endl;


	
}


/*--------------大小端转换-----------------*/
typedef unsigned int uint_32;
typedef unsigned short uint_16;
//16位
#define BSWAP_16(x) \
(uint_16)((((uint_16)(x) & 0x00ff) << 8) | \
(((uint_16)(x) & 0xff00) >> 8) \
)

//32位               
#define BSWAP_32(x) \
(uint_32)((((uint_32)(x) & 0xff000000) >> 24) | \
(((uint_32)(x) & 0x00ff0000) >> 8) | \
(((uint_32)(x) & 0x0000ff00) << 8) | \
(((uint_32)(x) & 0x000000ff) << 24) \
)
//无符号整型16位  
uint_16 bswap_16(uint_16 x)
{
	return (((uint_16)(x) & 0x00ff) << 8) | \
		(((uint_16)(x) & 0xff00) >> 8);
}
//无符号整型32位
uint_32 bswap_32(uint_32 x)
{
	return (((uint_32)(x) & 0xff000000) >> 24) | \
		(((uint_32)(x) & 0x00ff0000) >> 8) | \
		(((uint_32)(x) & 0x0000ff00) << 8) | \
		(((uint_32)(x) & 0x000000ff) << 24);

}


void mapTest()
{
	map<string, int> mapStrToInt;
	mapStrToInt.insert(make_pair("aaa",1));
	mapStrToInt.insert(make_pair("bbb", 2));

	cout << mapStrToInt.size() << endl;
	int i = mapStrToInt.size();
	cout << i << endl;
	unsigned int j = mapStrToInt.size();
	cout << j << endl;

	DisplayMapContents(mapStrToInt);

	auto pairFound = mapStrToInt.find("bbb");
	if (pairFound != mapStrToInt.end())
	{
		cout << pairFound->first;
		cout << pairFound->second;
	}

}



void structInitStruct()
{

	MyStruct *my = new MyStruct();
my->a = 1;

cout << "a=" << my->a << "b=" << my->b << "c=" << my->d << endl;
memset(my, 0, sizeof(MyStruct));

cout << "a=" << my->a << "b=" << my->b << "c=" << my->d << endl;
my->a = 2;

cout << "a=" << my->a << "b=" << my->b << "c=" << my->d << endl;
MyStruct m;

my = &m;
cout << "a=" << my->a << "b=" << my->b << "c=" << my->d << endl;
}


thread *t1;
thread *t2;





void testVector3(int count)
{
	vector<MyStruct> tenElement;
	cout << "tenElement.size():" << tenElement.size() << endl;
	clock_t start = clock();
	MyStruct s = { 1,1,"a" };
	int i = 0;
	for (; i < count; i++)
	{
		s.d = "a" + to_string(i);
		tenElement.push_back(s);
	}
	clock_t end = clock();
	cout << "生成tenElement "<<count<<"个对象 耗时" << end - start << "MILLISECOND" << endl;;
	start = clock();
	for (vector<MyStruct>::iterator stemp = tenElement.begin(); stemp != tenElement.end(); ++stemp)
	{
		if (stemp->a == count)
			break;
	}
	end = clock();
	cout << "遍历tenElement "<<count<<"个对象 耗时" << end - start << "MILLISECOND" << endl;;

	//vector<MyStruct>::iterator it = tenElement.begin();



}

void compareTestvectorAndList()
{
	int count[5] = { 1000000,100000,10000,1000,100 };
	for (int i = 0; i < 5; i++)
	{
		cout << "***********第" << i << "次测试***********" << endl;
		testVector3(count[i]);
		testList3(count[i]);
	}

}

class Depth
{
public:
	char instrument[31];
	string strtime;
	int bid1;
	int bidV1;
	int ask1;
	int askV1;
	int last;
	int lastV;
	void init()
	{
		bid1 = rand()%100;
		ask1 = bid1 + 2;
		bidV1 = askV1 = 10;
		last = 2;
		lastV = 3;
		strtime = getTime();

	}
};
void testlist4(int count)
{
	Depth *d = new Depth();
	list<Depth> depthList;
	for (int i = 0; i < count; i++)
	{
		d->init();
		
		depthList.push_back(*d);
	}
	cout << "个数 "<< depthList.size() << endl;
	clock_t start = clock();
	int avg=0;
	int high=0;
	int i = 0;
	
	for (list<Depth>::iterator stemp = depthList.begin(); stemp != depthList.end(); ++stemp)
	{
		i++;
		//if(strcmp(stemp->strtime.c_str(),getTime().c_str())==0)
		avg += stemp->last;
			//avg = (stemp->last + avg*(i-1)) / i;
	}
	avg = avg / i;
	clock_t end = clock();
	cout << "耗时为：" <<end - start << "MILLISECOND" << endl;
	cout << "avg = " << avg;
}
//使用find_if，该函数可以定义比较函数
typedef struct finder_t
{
	finder_t(string s) :instrument(s)
	{}
	bool operator()(Depth t)
	{
		if (strcmp(t.instrument, instrument.c_str()) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	string instrument;
}finder_t;


bool findFun(Depth& d, string s)
{
	if (strcmp(d.instrument, s.c_str()) == 0)
		return true;
	else
		return false;
}

void testFindIF(int count)
{
	Depth *d = new Depth();
	vector<Depth> depthList;
	for (int i = 0; i < count; i++)
	{
		d->init();
		strcpy_s(d->instrument, "a");
		strcat_s(d->instrument, to_string(i).c_str());
		depthList.push_back(*d);
	}
	cout << "个数 " << depthList.size() << endl;

	string findValue = "a10000";

	finder_t f(findValue);
	clock_t start;
	clock_t end;
	start= clock();
	vector<Depth>::iterator result = find_if(depthList.begin(), depthList.end(), f);
	 end = clock();
	cout << "耗时为：" << end - start << "MILLISECOND" << endl;

	start = clock();

	for (vector<Depth>::iterator stemp = depthList.begin(); stemp != depthList.end(); ++stemp)
	{
		if (strcmp(stemp->instrument, findValue.c_str()) == 0)
			break;
	}
	end = clock();
	cout << "耗时为：" << end - start << "MILLISECOND" << endl;

	auto findCallable = std::bind(findFun, std::placeholders::_1, findValue);
	start = clock();
	
	 result = find_if(depthList.begin(), depthList.end(), findCallable);
	end = clock();
	cout << "耗时为：" << end - start << "MILLISECOND" << endl;
	
}




int main(int argc, char *argv[])
{
	//testFindIF(count);
	//testFindIF(count);

	testListFind();
	system("pause");
	return EXIT_SUCCESS;
}






