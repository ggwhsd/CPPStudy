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
	struct stat st;
	int ret = stat(argv[1],&st);
	if(ret==-1)
		perror("stat failed");
	else
	{
		printf("%d",st.st_size);
	}
}
