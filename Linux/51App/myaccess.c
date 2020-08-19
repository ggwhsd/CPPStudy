#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
int main(int argc, char* argv[1]       ) 
{
	if(argc<2)
	{
		printf("./a.out filename");
		exit(1);
	}
	int ret = access(argv[1],W_OK);
	if(ret==-1)
		perror("access");
	else
	{
		printf("you have write access");
	}
}
