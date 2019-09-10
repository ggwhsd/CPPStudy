#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>

/*
	a word dictionary  
*/

void fun_ctrl_c();
void add(FILE *fp, int *n)
{
	char s[80];
	if((fseek(fp,0,SEEK_END))==-1)
	{
		printf("add failed\n");
		exit(1);
	}
	printf("please enter the word:\n");
	fgets(s,80,stdin);
	fputs(s,fp);
	fputc('\0',fp);
	(*n)=(*n)+2;
	printf("totally %d words !\n",(*n)/2);
	fclose(fp);
	system("./dic");
}

void seek(FILE *fp, int *n)
{
	int flag=0;
	char s[20],t[80],a;
	rewind(fp);
	printf("please enter the word you want to seek:");
	fgets(s,20,stdin);
	while((fgets(t,80,fp))!=NULL)
	{
		if(strcmp(t,s)==0)
		{
		   flag=1;
		   break;
		}
	}
	if(flag==0)
	{
		printf("cannot find the word, would you like to add it?(y?)\n");
		scanf("%c",&a);
		getchar();
		if(a=='y')
			add(fp,n);
		fclose(fp);
		system("./dic");
	}
	else
	{
		fgets(t,80,fp);
		printf("%s :%s",s,t);
		fclose(fp);
		system("./dic");
	}
}

void review(FILE *fp, int *n)
{
	(void)signal(SIGINT, fun_ctrl_c);
	int i,m;
	char s[20];
	srand((int)time(0));
	while(1)
	{
		i=(int)(1.0*(*n)*rand()/(RAND_MAX+1.0));
		if((i%2)==0)
			i++;
		rewind(fp);
		for(m=0;m<i;m++)
		{
			fgets("s",20,fp);

		}
		printf("%s",s);
		getchar();

	}
}



void fun_ctrl_c()
{
	char c;
	printf("do you want to quit? \n");
	scanf("%c",&c);
	if(c=='y')
	{
		(void)signal(SIGINT,SIG_DFL);
		system("./dic");
		exit(0);

	}
	return;
}


int main()
{
	char t;
	int cho,status,n,i=0;
	FILE *fp;
	pid_t result,wpid;
	if((fp=fopen("wlist","a+"))==NULL)
	{
		perror("file open failed:");
		exit(1);
	}
	result=fork();
	if(result<0)
	{
		perror("error:");
		exit(1);
	}
	else if(result==0)
	{
		rewind(fp);
	while((t=fgetc(fp))!=EOF)
	{
		if(t=='\n') i++;

	}
	printf("totally %d words!\n",i/2);
	exit(i);
	}
	else
	{
		printf("1----add new words\n 2-------seek a word\n 3--------review \n press any other key to quit\n");
		scanf("%d",&cho);
		getchar();
		wpid=wait(&status);
		n=WEXITSTATUS(status);
		switch(cho){
			case 1:
				add(fp,&n);
				break;
			case 2:
				seek(fp, &n);
				break;
			case 3:
				review(fp,&n);
				break;
			case 4:
				fclose(fp);
				printf("thank you for using dictionary");
				sleep(1);
				break;
		
		}
	}

}
