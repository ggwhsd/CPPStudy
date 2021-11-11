
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include "./gen/hello.h"
using namespace std;

template<class T> 
class A
{
    public :
    T get();
    T getMax(T a, T b);
    A(){ 
        
        //data = new T();
        std::cout<<"A()"<<endl;
        }

    private:
    T data;

};

template<class T>T A<T>::get()
{
    return data;
}

template<class T>
T A<T>::getMax(T a, T b)
{
    if(a>b)
        return a;
    else
    {
        return b;
    }
    
}



int main(int argc,char** argv)
{
    cout<<"helloworld,here is the first cpp in vscode"<<endl;
    cout<<"test so lib"<<endl;
    int a;
    int b;
    cin>>a>>b;
    cout<<"guMax="<<guMax(a,b)<<endl;

    A<int> a1;
    A<double> b1;

    vector<A<int> > v1;


}