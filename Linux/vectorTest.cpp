#include <vector>
#include <iostream>
#include <chrono>
#include <string>
using namespace std;
struct MyStruct
{
	int a;
	int b;
	string d;
	//used in DisplayContents via cout
	operator const char*() const
	{
		return d.c_str();
	}

};


//使用reserve的方式之后，初始化时间
void testVectorTime2(int number)
{
	vector<MyStruct> tenElement;
	tenElement.reserve(number);
	cout << "tenElement.size():" << tenElement.size() << endl;
	cout << "tenElement.capacity():" << tenElement.capacity() << endl;
	clock_t start = clock();
	MyStruct s = { 1,1,"a" };
	int i = 0;
	for (; i < number; i++)
	{
		s.a = i;
		tenElement.push_back(s);
	}
	clock_t end = clock();
	cout << "生成tenElement "<< number <<"个对象 耗时" <<(double)(end - start)/CLOCKS_PER_SEC << "SECOND" << endl;
	start = clock();
	for (size_t i = number; i > 0; i--)
	{
		if (tenElement[i].a == 2)
		{
			cout << tenElement[i].a << endl;
			break;
		}
	}
end = clock();
cout << "遍历tenElement "<<number<<"个对象 耗时" << (double)(end - start)/CLOCKS_PER_SEC << "SECOND" << endl;;

}


int main (int argc, char **argv)
{
	testVectorTime2(atoi(argv[1]));
	return 0;	
}
