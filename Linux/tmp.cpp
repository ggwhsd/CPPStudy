#include <iostream>
using namespace std;

class Y
{
public:
	void a()
	{
		cout<<"yes"<<endl;
	}
};

int main()
{
	cout<<&Y::a<<endl;
	Y y;
	cout<<&y<<endl;
	void(Y::*ptr)()=&Y::a;
	
	(y.*ptr)();

}
