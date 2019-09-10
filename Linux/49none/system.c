#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#define DELAY 60
int main()
{
time_t now;
struct tm *p;
while(1)
{
   now = time(NULL);
   sleep(DELAY);
   p = localtime(&now);
   if(p->tm_hour == 23){
	   system("echo time is 23 clock > test.txt");
	   break;
   }
}
return 0;
}
