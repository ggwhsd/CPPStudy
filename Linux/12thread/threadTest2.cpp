#include <iostream>
#include <thread>
#include <chrono>
int volatile countp=0;
int counts=0;
clock_t start;
clock_t end;
void thread_function() {
  start=clock();
  for (int i = 0; i < 1000000; i++)
  {
   countp++;
   // std::cout << "countp = "<<++countp << '\t' ;
  }
}

void thread_s()
{
	int i=100000000;
	while(1)
	{		
		if(countp>=1000000){
		end=clock();
		std::cout<<"time = "<< end-start <<"counts = "<<counts<<'\t'<<"countp = "<<countp<<std::endl;

		break;
		}
	}
}
 
int main() {
  
  std::thread threadObj(thread_function);
  std::thread threadS(thread_s);
 threadObj.join();
  threadS.join();
  
  std::cout<<CLOCKS_PER_SEC<<std::endl;
  return 0;

}

