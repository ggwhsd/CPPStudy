#pragma once
#include <vector>
#include <iostream>
using namespace std;

/*
vector的优势在于遍历效率高
list的优势在于增加和删除快
假如想在一个固定的内存空间中，循环使用数据，且遍历的使用次数和修改次数都很多。
那就是基于vector做一个循环数组结构，快速遍历，快速修改。

在使用的cpp文件代码之前里面要定义具体类型，比如 template class CicleVector<int>;
*/
template<typename T>
class CicleVector
{
private:
	int maxSize; //数组长度
	int front; //用来记录待删到哪儿了的索引
    int rear; //用来记录待添加到哪儿了的索引
	int length; //当前元素数
	vector<T> vInt;

private:

	
public:
	CicleVector(int capacity);
	bool push(T);
	bool remove();
	T back();
	T pop();
	int size();
	//使用一个单位来作为队列是否满的标记
	bool isFull();
	bool empty();
	void display();
	void display2();

	bool get(int index,T& t);
};