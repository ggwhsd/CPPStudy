#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define N 5
int main(void)
{
	int id = fork();
	if(id==0)
	{
		printf(" child %d ",getpid());
	}
	else
	{	

		
		sleep(5);
		
	int ret = kill(SIGKILL, id);
	if(ret)
		printf("kill %d",id);
	
	}
	return 0;
}
