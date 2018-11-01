#include <thread>
#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mut;
queue<int> data_queue;
condition_variable data_cond;
void data_preparation_thread()
{
    cout<<"preparation\n";
	lock_guard<mutex> lk(mut);
cout<<"lock guard\n";	
    this_thread::sleep_for(chrono::milliseconds(5000));

	data_queue.push(1);
	data_cond.notify_one();
	cout<<"notify\n";

}

void data_processing_thread()
{
    cout<<"process begin\n";
	unique_lock<mutex> lk(mut);
	cout<<"unique lock\n";
	data_cond.wait(lk,[]{return !data_queue.empty();});
	cout<<"wait\n";
	data_queue.pop();
	lk.unlock();
	
}
int main()
{
  thread t0(data_preparation_thread);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  thread t1(data_processing_thread);
  t1.join();
  t0.detach();
  return 0;
}
