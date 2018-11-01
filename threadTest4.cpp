#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
std::mutex mt;
int countp=0;
int counts=0;
clock_t start;
clock_t end;
struct my
{
	int i;
	int j;

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
  
  std::thread threadS(thread_s);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  m1->i=2;
  m1->j=2;
  threadS.join();
  std::cout<<CLOCKS_PER_SEC<<std::endl;
  return 0;

}

