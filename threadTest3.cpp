#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
std::mutex mt;
int countp=0;
int counts=0;
clock_t start;
clock_t end;
void thread_function() {
  start=clock();
  mt.lock();
  for (int i = 0; i < 50; i++)
  {
  
   countp++;
 
   // std::cout << "countp = "<<++countp << '\t' ;
  }
  mt.unlock();
}


void thread_s()
{	
			mt.lock();
			countp+=1;
			mt.unlock();
		end=clock();
		std::cout<<"time = "<< end-start <<"counts = "<<counts<<'\t'<<"countp = "<<countp<<std::endl;
}
 
int main() {
  
  std::thread threadObj(thread_function);
  std::thread threadS(thread_s);
 threadObj.join();
  threadS.join();
  
  std::cout<<CLOCKS_PER_SEC<<std::endl;
  return 0;

}

