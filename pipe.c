#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int main()
{
	pid_t result;
	int num;
	int pipe_fd[2];
	FILE *fp;
	char buf[500];
	memset(buf,0,sizeof(buf));
	printf("creating tunnel ... ... \n");
	if(pipe(pipe_fd)<0)
	{
		printf("can not create a tunnel");
		return -1;
	}
	result=fork();
	if(result<0)
	{
		printf("can not create a process");
		exit(1);
	}
	else if(result == 0)
	{
		close(pipe_fd[1]);
		if((num=read(pipe_fd[0],buf,500))>0)
			printf("the result from son process:%s\n",buf);
		close(pipe_fd[0]);
		exit(0);
	}
	else
	{
		close(pipe_fd[0]);
		fp=popen("ls -l","r");
		num = fread(pipe_fd[1],sizeof(char),500,fp);
		pclose(fp);
		close(pipe_fd[1]);
		waitpid(result,NULL,0);
		exit(0);
	}
	return 0;
}
