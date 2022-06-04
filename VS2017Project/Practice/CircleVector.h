#pragma once
#include <vector>
#include <iostream>
using namespace std;

/*
vector���������ڱ���Ч�ʸ�
list�������������Ӻ�ɾ����
��������һ���̶����ڴ�ռ��У�ѭ��ʹ�����ݣ��ұ�����ʹ�ô������޸Ĵ������ܶࡣ
�Ǿ��ǻ���vector��һ��ѭ������ṹ�����ٱ����������޸ġ�

��ʹ�õ�cpp�ļ�����֮ǰ����Ҫ����������ͣ����� template class CicleVector<int>;
*/
template<typename T>
class CicleVector
{
private:
	int maxSize; //���鳤��
	int front; //������¼��ɾ���Ķ��˵�����
    int rear; //������¼����ӵ��Ķ��˵�����
	int length; //��ǰԪ����
	vector<T> vInt;

private:

	
public:
	CicleVector(int capacity);
	bool push(T);
	bool remove();
	T back();
	T pop();
	int size();
	//ʹ��һ����λ����Ϊ�����Ƿ����ı��
	bool isFull();
	bool empty();
	void display();
	void display2();

	bool get(int index,T& t);
};