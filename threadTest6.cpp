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

  std::cout<<"threadS is running"<<std::endl;
	int i=0;
	while(i<1000000)
	{
        if(m1->timestamp <= m1->lastDealtime){
		m1->i=i;
		m1->j=i;
		m1->timestamp=clock();
		i++;
		}
	}
	
	std::cout<<"threadS "<<"i="<<m1->i<<" j="<<m1->j<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	start=clock();
	isOver=false;
}


void thread_r()
{
	
  std::cout<<"threadR is running"<<std::endl;
    bool flag = true;
	while(isOver)
	{
	if(m1->lastDealtime<m1->timestamp)
	{	
		if(flag){
		std::cout<<"threadR "<<" diffclock="<<clock() - m1->timestamp<<std::endl;
		std::cout<<"threadR "<<" i="<<m1->i<<" j="<<m1->j<<std::endl;
		flag=false;
		}
		
		if(m1->i != m1->j)
		{
			std::cout<<"[mark]"<<" i="<<m1->i<<" j="<<m1->j<<std::endl;
			
		}

		m1->lastDealtime=clock();
		
	}
	}
	endt=clock();
	std::cout<<" isOver diffcock="<<endt-start<<std::endl;
	
}
 
int main() {
  m1 = new my();
  m1->lastDealtime=clock();
  m1->timestamp=m1->lastDealtime;
  std::thread threadR(thread_r);
  threadR.detach();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::thread threadS(thread_s);
  threadS.join();
  std::cout<<CLOCKS_PER_SEC<<std::endl;
  return 0;

}

