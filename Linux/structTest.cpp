#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;
std::mutex mt;
int countp=0;
int counts=0;
clock_t start;
clock_t end;
struct dat
{
	char s1[10];
	char s2[10];
	double s;
};
struct my
{
	int i;
	int j;
    dat k;
};
my* m1;

void test(my* s)
{
	int i=0;
	while(i<100000)
	{
		i++;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(2));
	std::cout<<"i="<<s->i<<" j="<<s->j<<std::endl;
}


void thread_s()
{	
    m1 = new my();
	m1->i=1;
	m1->j=1;
			test(m1);
}
 
int main() {
  
  /*std::thread threadS(thread_s);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  m1->i=2;
  m1->j=2;
  threadS.join();
  std::cout<<CLOCKS_PER_SEC<<std::endl;
  */
  m1 = new my();
  memset(m1,0,sizeof(my));
  m1->i=1;
  m1->k.s=1.0;
  strcpy(m1->k.s1,"m1");
  cout<<"m1------"<<endl;
  cout<<m1->i<<endl;
  cout<<m1->j<<endl;
  cout<<m1->k.s1<<endl;
  cout<<m1->k.s2<<endl;
  cout<<m1->k.s<<endl;
  
  my m2;
  m2=*m1;
  cout<<"m2------"<<endl;
 cout<<&m2<<endl;
 cout<<m2.i<<endl;
  cout<<m2.j<<endl;
  cout<<m2.k.s1<<endl;
  cout<<m2.k.s2<<endl;
  cout<<m2.k.s<<endl;
  
  my m3;
  m3 = m2;
  m2.i=2;
  cout<<"m3------"<<endl;
  cout<<&m3<<endl;
  cout<<m3.i<<endl;
  cout<<m3.j<<endl;
  cout<<m3.k.s1<<endl;
  cout<<m3.k.s2<<endl;
  cout<<m3.k.s<<endl;
    
  my *m4 = new my();
  *m4 = m2;
  cout<<"m4-----"<<endl;
  cout<<m4<<endl;
  cout<<m4->i<<endl;
  cout<<m4->k.s1<<endl;
return 0;

}

