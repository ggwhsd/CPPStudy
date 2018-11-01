#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
	int *p;
	int fd=open("Liu",O_RDWR);
	if(fd<0)
	{
		printf("open error");
		exit(1);
	}
	p = mmap(NULL, 6, PROT_WRITE, MAP_SHARED, fd, 0);
	if(p==MAP_FAILED)
	{
		printf("mmap");
		exit(1);

	}
	close(fd);
	p[0]=0x30313233;

	munmap(p,6);
	return 0;
}

