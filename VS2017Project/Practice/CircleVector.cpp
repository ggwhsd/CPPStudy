
#include "CircleVector.h"

template class CicleVector<int>;

template <typename T>
CicleVector<T>::CicleVector(int capacity):front(0), rear(0), length(0), maxSize(capacity+1),vInt(capacity + 1)
{

}

template<typename T>
bool CicleVector<T>::push(T data)
{
	if (isFull())
	{
		
		return false;
	}

	vInt[rear] = data;
	rear = (rear + 1) % maxSize;
	length++;
	return true;
}

template<typename T>
bool CicleVector<T>::remove()
{
	if (empty())
	{
		
		return false;
	}
	else
	{
	
		vInt[front] = 0;
		front = (front + 1) % maxSize;
		length--;
		return true;
	}
}

template<typename T>
T CicleVector<T>::back()
{
	
	return vInt[front];
	
}

template<typename T>
T CicleVector<T>::pop()
{
	T t = vInt[front];
	remove();
	return t;
}

template<typename T>
int CicleVector<T>::size()
{
	return length;
}

template<typename T>
bool CicleVector<T>::isFull()
{
	return ((rear + 1) % maxSize == front);
}

template<typename T>
bool CicleVector<T>::empty()
{
	return front == rear;
}

template<typename T>
void CicleVector<T>::display()
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

template<typename T>
void CicleVector<T>::display2()
{
	int i = front;
	cout << "数组内容为" << endl;
	if (front < rear)
	{
		while (i < rear)
		{
			cout << vInt[i] << " ";
			i++;
		}
	}
	else
	{
		while ((i%maxSize)!=rear)
		{
			cout << vInt[(i%maxSize)] << " ";
			i++;
		}
	}
	cout << endl;
}

template<typename T>
bool CicleVector<T>::get(int index, T& t)
{
	if (empty())
		return false;
	if (index > length)
		return false;
	if (front < rear)
	{
		index = index + front;
		t = vInt[index];

	}
	else
	{
		index = (index + front) % maxSize;
		t= vInt[index];
	}


	return true;
}
