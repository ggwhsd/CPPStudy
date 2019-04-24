#include "stdafx.h"
#include "CircleVector.h"

CicleVector::CicleVector()
{
	maxSize = 10;
	vInt.reserve(maxSize);
	int i=0;
	while(i < (int)(vInt.capacity()))
	{
		vInt.push_back(0);
		i++;
	}
	front = 0;
	rear = 0;
}

void CicleVector::add(int data)
{
	if (isFull())
	{
		cout << "队列满" << endl;
		return;
	}
	
	vInt[rear]=(data);
	rear = (rear + 1) % maxSize;
}

void CicleVector::remove()
{
	if (isEmpty())
	{
		cout << "空" << endl;
		return;
	}
	else
	{
	
		vInt[front] = 0;
		front = (front + 1) % maxSize;
	}
}

bool CicleVector::isFull()
{
	return ((rear + 1) % maxSize == front);
}

bool CicleVector::isEmpty()
{
	return front == rear;
}

void CicleVector::display()
{
	vector<int>::iterator iter = vInt.begin();
	cout << "数组内容为" << endl;
	while (iter != vInt.end())
	{
		cout << *iter << " ";
		iter++;
	}
	cout << endl;
}
