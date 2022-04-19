#pragma once
#include <iostream>
#include <string>
using namespace std;

class PlaceNew
{
public :
	PlaceNew()
	{
		cout << __FUNCTION__ << endl;
	}
	PlaceNew(int a,int b) :v1(a),v2(b)
	{
		cout << __FUNCTION__ << "-"<< a<<"-"<<b<< endl;
		s1 = "hello";
	}
	~PlaceNew()
	{
		cout << __FUNCTION__ << "-" << v1 << "-" << v2 << endl;
	}
	int GetValue()
	{
		return v1 + v2;
	}
	string GetS1()
	{
		return s1;
	}

private:
	int v1;
	int v2; //��ʹ�����������������û�������ֵ���ڴ��л��Ǵ��ڵġ�
	string s1;  //��������������������֮���Ϊ���ַ���
};

// �������ӣ��Ϳ��Կ�����placement�������Ѿ�����õ��ڴ���ֱ�Ӵ��������Ҿ��ú��̳߳صı���ԭ�����ڴ����θ��ã�ǰ���Ǵ����Ա�׼���ṩ�Ĺ��ܣ������ǻ�������֮�Ͽ����Ĺ��ܡ�
void TestPlacementNew()
{
	char *ptr_memory = new char[1024]{ 0 };

	PlaceNew *pNormalNew1 = new PlaceNew(1,1);
	cout << "pNormalNew1 getvalue=" << pNormalNew1->GetValue() << endl << endl;
	delete pNormalNew1;

	PlaceNew *pPlaceNew1 = new (ptr_memory) PlaceNew(1, 2);
	cout << "Address = " << pPlaceNew1 <<endl;;
	cout << "pPlaceNew1 getvalue = " << pPlaceNew1->GetValue() << endl;
	cout << "pPlaceNew1 getS1 = " << pPlaceNew1->GetS1() << endl;
	pPlaceNew1->~PlaceNew();
	cout << "after ~PlaceNew()" << endl;
	cout << "pPlaceNew1 getvalue = " << pPlaceNew1->GetValue() << endl;
	cout << "pPlaceNew1 getS1 = " << pPlaceNew1->GetS1() << endl << endl;;

	PlaceNew *pPlaceNew2 = new (ptr_memory) PlaceNew(1, 2);
	cout << "Address = " << pPlaceNew2 << endl;;
	cout << "pPlaceNew2 getvalue = " << pPlaceNew2->GetValue() << endl;;
	

	cout << "Sizeof PlaceNew = " << sizeof(PlaceNew) << endl;
	//��Ϊ<<���ַ���ָ��ֱ������ַ�����ֵ��������ָ���ֵ�����������Ҫ����ַ����ĵ�ַ��ͨ������תΪintָ�룬�Ϳ�����ʾ��ַ�ˣ�
	cout << "Address PlaceNew + 1= " << (int *)(ptr_memory + sizeof(PlaceNew)) << endl;
	
	PlaceNew *pPlaceNew3 = new (pPlaceNew2 +1) PlaceNew(1, 2);
	cout << "Address (new (pPlaceNew2 +1))= " << pPlaceNew3 << endl;;
	cout << "pPlaceNew2 getvalue = " << pPlaceNew3->GetValue() << endl;;
	pPlaceNew3->~PlaceNew();
	cout << "after ~PlaceNew()" << endl;
	cout << "pPlaceNew2 getvalue = " << pPlaceNew3->GetValue() << endl;;

}