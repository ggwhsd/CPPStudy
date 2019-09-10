#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char * argv[])
{
	pid_t pid;
	if((pid=fork())<0)
		printf("error");
	else if(pid==0)
	{
		execl("/bin/ls","ls","-l","/home",(char*)0);

	}
	else
		printf("father ok");
	return 0;
}
