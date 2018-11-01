#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>

void init_deamon(void);

int main()
{
	char IP[13],cmd[100]="ifconfig eth0";
	FILE *fp, *fp1;
	int offset;
	init_deamon();
	while(1)
	{
		if((fp = fopen("IP","r"))==NULL)
		{
			printf("failed to open IP");	
			exit(1);
		}
		if((fp1 = fopen("IPLOG","a+"))==NULL)
		{
			printf("failed to open IPLOG");	
			exit(1);
		}
		srand((int)time(0));
		offset = rand()/(RAND_MAX+1.0)*10.0;
		fseek(fp,offset*13,SEEK_SET);
		fread(IP,13,1,fp);
		strcat(cmd,IP);
		fprintf(fp1,"正在运行%s",cmd);
		system(cmd);
		rewind(fp);
		strcpy(cmd,"ifconfig eth0 ");
		fclose(fp);
		fclose(fp1);
		sleep(30);

	}
}
void init_deamon(void)
{
	pid_t child;
	int i;
	child = fork();
	if(child>0)
	{
		exit(0);
	}
	if(child<0)
	{
		printf("fork error\n");
		exit(1);
	}
	setsid();
	chdir("/home/nearu/c_prog");
	umask(0);
	for(i=0; i<NOFILE; i++)
		close(i);
	return;

}
