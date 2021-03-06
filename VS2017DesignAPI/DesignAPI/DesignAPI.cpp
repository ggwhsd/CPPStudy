// DesignAPI.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "./autoTimer.h"
#include <iostream>
#include "observer.h"
#include "./stack.h"

void testAutoTimer()
{
	AutoTimer1 *at = new AutoTimer1("Pimpl_Timer");
	int rtn;
	std::cin >> rtn;
	delete at;
	rtn;
	std::cin >> rtn;
}

void testObserver()
{
	MyObserver observer1("ob1");
	MyObserver observer2("ob2");
	MyObserver observer3("ob3");
	MySubject subject;
	subject.Subscribe(MySubject::ADD, &observer1);
	subject.Subscribe(MySubject::ADD, &observer2);
	subject.Subscribe(MySubject::REMOVE, &observer2);
	subject.Subscribe(MySubject::REMOVE, &observer3);
	
	subject.Notify(MySubject::ADD);
	subject.Notify(MySubject::REMOVE);

	subject.UnSubscribe(MySubject::REMOVE, &observer3);
	subject.UnSubscribe(MySubject::ADD, &observer2);
	subject.Notify(MySubject::ADD);
	subject.Notify(MySubject::REMOVE);
}

void testTemplateStack()
{
	IntStack s;
	s.Push(3);
	std::cout<<s.IsEmpty()<<std::endl;
	std::cout << s.Pop() << std::endl;;
	s.Push(5);
	std::cout << s.IsEmpty() << std::endl;
	std::cout << s.Pop() << std::endl;;
	
}

class ByteTestA
{
	bool a;
	bool b;
	int c;
	bool d;
	int e;

};
class ByteTestB
{
	bool a;
	bool b;
	bool d;
	int c;
	int e;

};
//成员变量按照从小打到排，所占内存空间要小一点。
void TestBytes()
{
	std::cout << "sizeof int " << sizeof(int) << std::endl;
	std::cout << "sizeofA " << sizeof ByteTestA << std::endl;
	std::cout << "sizeofB " << sizeof ByteTestB << std::endl;
};

int main()
{
	TestBytes();
	system("pause");
    return 0;
}

