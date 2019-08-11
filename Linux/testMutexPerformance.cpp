#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;
/*
	compare performance between using mutex and no mutex

*/
std::mutex mt;
clock_t start=0;
clock_t endt=0;
struct my
{
	int i;
	int j;
	clock_t timestamp;
	clock_t lastDealtime;

};
my* m1;
bool isOver=true;
int countLimit = 100000;

inline void timeConsumeWork(int &i)
{
i++;

}
void thread_s2()
{
  int i=0;
  start=clock();


  while(i<countLimit)
  {
  	//mt.lock();
	
timeConsumeWork(i);
	//mt.unlock();
  }
  endt = clock();

  std::cout<<" no mutex perform ="<<(double)(endt-start)/countLimit<<std::endl;

      
  //this_thread::sleep_for(chrono::milliseconds(100000));
	
	isOver=false;
	

}
void thread_s()
{
  int i=0;
  start=clock();


  while(i<countLimit)
  {
  	mt.lock();
	timeConsumeWork(i);
	mt.unlock();
  }
  endt = clock();

  std::cout<<" mutex perform ="<<(double)(endt-start)/countLimit<<std::endl;

      
  //this_thread::sleep_for(chrono::milliseconds(100000));
	
	isOver=false;
	

}


 
int main() {

  
  thread threadS(thread_s);
  threadS.join();
  this_thread::sleep_for(chrono::milliseconds(1000));
  thread threadS2(thread_s2);
  threadS2.join();


  std::cout<<"one seconds = "<<CLOCKS_PER_SEC<<std::endl;
  return 0;

}

