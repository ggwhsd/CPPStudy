#pragma once
#include <vector>
#include <iostream>
#include <vector>
using namespace std;

/*
vector的优势在于遍历效率高
list的优势在于增加和删除快
假如想在一个固定的内存空间中，循环使用数据，且遍历的使用次数和修改次数都很多。
那就是基于vector做一个循环数组结构，快速遍历，快速修改。
*/

class CicleVector
{
private:
	int maxSize; //数组长度
	int front; //用来记录待删到哪儿了的索引
    int rear; //用来记录待添加到哪儿了的索引
	vector<int> vInt;
public:
	CicleVector();
	void add(int);
	void remove();
	bool isFull();
	bool isEmpty();
	void display();



};