#include <iostream>
using namespace std;

class CAdd
{
public:
    CAdd():m_nSum(0) { NULL; }
    int operator()(int i)　　//重载 （） 运算符
    {
          m_nSum += i;
          return m_nSum;
    }

    int Sum() const 
    {
        return m_nSum;
    }
    void functionCallback( function<int(int)> f)
	{
		cout<<__func__<< " "<<f(100) <<endl;
	}
private:
    int m_nSum;
};


class Tadd
{
public:
	int Add(int x,int y)
	{
		return x+y;
	}
};

int main() 
{
    CAdd add;
    function<int (int)> f1 = add;
    function<int (int)> f2 = ref(add);

    cout << f1(10) << "," << f2(10) << "," << add.Sum() << endl;
    
	add.functionCallback(f1);
     
	function<int(Tadd*,int,int)> f3 = &Tadd::Add;
	Tadd tdd;
	cout<<"f3"<<f3(&tdd,2,3)<<endl;

	return 0;
}
