#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;
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
void thread_s()
{
  int i=0;
  while(i<1000000)
  {
  	i*i;
	i++;
  }
  std::cout<<"threadS is running"<<std::endl;
	mt.lock();
      
  this_thread::sleep_for(chrono::milliseconds(100000));
	start=clock();
	isOver=false;
	mt.unlock();
}


void thread_r()
{
	clock_t endt1;
  std::cout<<"threadR is running"<<std::endl;
	while(1)
	{
//	mt.lock();
	if(isOver==false)
	{ 
	endt1=clock();
	
std::cout<<" isOver diffcock="<<endt1-start<<std::endl;
	
//	mt.unlock();
	break;}
//	mt.unlock();
	}
	
}
 
int main() {
  m1 = new my();
  std::thread threadR(thread_r);
  threadR.detach();
  thread threadR1(thread_r);
  threadR1.detach();
 // thread threadR2(thread_r);
 // threadR2.detach();
 // thread threadR3(thread_r);
 // threadR3.detach();
  this_thread::sleep_for(chrono::milliseconds(1000));
  thread threadS(thread_s);
  threadS.join();
  
  std::cout<<CLOCKS_PER_SEC<<std::endl;
  return 0;

}

