#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <syslog.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>

int main()
{
	pid_t child1;
	FILE *fp;
	int i;
	int flag,nf,nnf;
	int nfile();
	time_t t;
	child1=fork();
	if(child1>0)
		exit(0);
	else if(child1<0)
	{
		printf("error");
		exit(1);
	}
	setsid();
	chdir("/tmp");
	umask(0);
	for(i=0;i<NOFILE;++i)
	{
		close(i);
	}
	nf=nfile(fp);
	while(1)
	{
		sleep(3000);
		fp=fopen("mail.log","a+");
		if(fp<0)
			printf("error file open\n");
		nnf=nfile(fp);
		if(nnf>nf)
		{
			fprintf(fp,"你有新的邮件到了\n");
			putchar(7);
		}
		else
		{
			fprintf(fp,"此刻时间段没有新邮件\n");
		}
		t = time(0);
		fprintf(fp,"%s",asctime(localtime(&t)));
		fclose(fp);
		nf = nnf;
	}
}

int nfile(FILE * fp)
{
	DIR *dir;
	struct dirent *ptr;
	int i = 0;
	dir=opendir("/var/spool/mail");
	while((ptr =readdir(dir))!=NULL)
	{
		i++;
		fprintf(fp,"%s\n",ptr->d_name);
	}
	closedir(dir);
	return i;
}
