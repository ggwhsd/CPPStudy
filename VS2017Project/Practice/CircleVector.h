#pragma once
#include <vector>
#include <iostream>
#include <vector>
using namespace std;

/*
vector���������ڱ���Ч�ʸ�
list�������������Ӻ�ɾ����
��������һ���̶����ڴ�ռ��У�ѭ��ʹ�����ݣ��ұ�����ʹ�ô������޸Ĵ������ܶࡣ
�Ǿ��ǻ���vector��һ��ѭ������ṹ�����ٱ����������޸ġ�
*/

class CicleVector
{
private:
	int maxSize; //���鳤��
	int front; //������¼��ɾ���Ķ��˵�����
    int rear; //������¼����ӵ��Ķ��˵�����
	vector<int> vInt;
public:
	CicleVector();
	void add(int);
	void remove();
	bool isFull();
	bool isEmpty();
	void display();



};