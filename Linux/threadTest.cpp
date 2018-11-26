#include <iostream>
#include <thread>
int countp=0;
int counts=0;

void thread_function() {
  for (int i = 0; i < 1200000; i++)
  {
   countp++;
   // std::cout << "countp = "<<++countp << '\t' ;
  }
}

void thread_s()
{
	int i=100000000;
	while(i>0)
	{
	if(countp>=counts)
	{
		counts++;
		std::cout<<"counts = "<<counts<<'\t'<<"countp = "<<countp<<std::endl;
	}
	i--;
	}
}
 
int main() {
  std::thread threadObj(thread_function);
  std::thread threadS(thread_s);
 threadObj.join();
  std::cout << "Exit of Main function" << std::endl;
  threadS.join();
  return 0;

}

