#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define EXITTOSIG "exit###"
#define SERVPORT 3333
#define BACKLOG 10
#define MAXDATASIZE 256

int sockfd;
int oppofd;
struct hostent *host;
struct sockaddr_in serv_addr;
struct sockaddr_in my_addr;
struct sockaddr_in remote_addr;
FILE *fp;
pthread_t ntid;

int sendexit();

void *pthread_recv(void *arg)
{
	int recvbytes;
	char rstr[MAXDATASIZE];
	char timestr[20];
	while(1)
	{
		recvbytes = recv(oppofd, rstr, MAXDATASIZE, 0);
		if(recvbytes == -1)
		{
			printf("recv failed\n");
			exit(1);
		}
		else if(strcmp(rstr, EXITTOSIG)==0)
		{
			printf("the opposite has exited. \n");
			fclose(fp);
			exit(0);
		}
		rstr[recvbytes]='\0';
		fprintf(fp,"%s",rstr);
		fprintf(fp,"\n");
		printf("\n%s",rstr);

	}
	pthread_exit((void*)1);
}

int main(int argc, char * argv[])
{
	int sin_size;
	int pth_err;
	int recvbytes;
	char buf[MAXDATASIZE];
	char sstr[MAXDATASIZE];
	char writing[MAXDATASIZE];
	char chatname[16];
	time_t timep;
	if(argc >= 2)
	{
		//client mode
		printf("\nwhat is your name?\n");
		gets(chatname);
		if((fp = fopen("./record_cus.txt","a+"))==NULL)
		{
			printf("creating fp failed!\n");
			exit(1);
		}

		if((host = gethostbyname(argv[1]))==NULL)
		{
			printf("gethost failed!\n");
			exit(1);
		}

		if((oppofd = socket(AF_INET, SOCK_STREAM, 0) )== -1)
		{
			printf("socket failed!\n");
			exit(1);
		}

		bzero(&serv_addr,sizeof(struct sockaddr_in));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(SERVPORT);
		serv_addr.sin_addr = *((struct in_addr *)host->h_addr);

		if(connect(oppofd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr))==-1)
		{
			printf("connect faild \n");
			exit(1);
		}

		if((recvbytes = recv(oppofd, buf, MAXDATASIZE, 0)) == -1)
		{
			printf("recv failed \n");
			exit(1);
		}
		buf[recvbytes] = '\0';
		printf("the first received information is :%s\n",buf);

		pth_err = pthread_create(&ntid, NULL, pthread_recv,NULL);
		
		while(1)
		{
			gets(writing);

			if(strcmp(writing, "exit")==0)
			{
				sendexit();
				exit(0);
			}
			
			strcpy(sstr, chatname);
			strcat(sstr, writing);
			strcat(sstr,"\n at ");
			time(&timep);
			strcat(sstr,asctime(gmtime(&timep)));
			strcat(sstr,"\n");
			fprintf(fp,  "%s",sstr);
			fprintf(fp," \n");
			printf("%s",sstr);
			if(send(oppofd, sstr, strlen(sstr), 0)==-1)
			{
				printf("send str failed!\n");
				exit(1);
			}

			memset(sstr, 0, MAXDATASIZE);
			memset(writing, 0, MAXDATASIZE);
		}
		close(oppofd);
		fclose(fp);
	}
	else
	{
		//server mode
		if((fp = fopen("./recode_ser.txt","a+")) == NULL)
		{
			printf("open file failed!\n");
			exit(1);
		}
        
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
			printf("socket failed !\n");
			exit(1);
		}
		bzero(&my_addr, sizeof(struct sockaddr_in));
		my_addr.sin_family = AF_INET;
		my_addr.sin_port = htons(SERVPORT);
		my_addr.sin_addr.s_addr = INADDR_ANY;
		if(bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr)))
		{
			printf("bind failed!\n");
			exit(1);
		}
		
		
		printf("server's IP:\n");
		system("ifconfig | grep inet\n");
	    printf("\n");

		printf("what's your name?\n");
		gets(chatname);
		if(listen(sockfd, BACKLOG) == -1)
		{
			printf("listen failed!\n");
			exit(1);

		}
		sin_size = sizeof(struct sockaddr_in);

		while(1)
		{
			oppofd = accept(sockfd, (struct sockaddr*)&remote_addr,&sin_size);
			if(oppofd == -1)
			{
				printf("accept failed!\n");
				exit(1);
			}

			else 
				break;
		}

		printf("received a connection of %s\n", inet_ntoa(remote_addr.sin_addr));
		if(send(oppofd, "successfully connected!\n", 26, 0) == -1)
		{
			printf("first sending failed!\n");
			exit(1);
		}
		pth_err = pthread_create(&ntid, NULL, pthread_recv, NULL);
		if(pth_err != 0)
		{
			printf("pthread failed!\n");
			exit(1);

		}

		while(1)
		{
			gets(writing);
			if(strcmp(writing,"exit")==0)
			{
				sendexit();
				exit(0);

			}
			strcpy(sstr, chatname);
			strcat(sstr, writing);
			strcat(sstr, " \n");
			strcat(sstr, " at ");
			time(&timep);
			strcat(sstr, asctime(gmtime(&timep)));
			strcat(sstr,"\n");

			fprintf(fp,"%s",sstr);
			fprintf(fp," \n");
			printf("\n%s",sstr);
			if(send(oppofd, sstr, strlen(sstr), 0)==-1)
			{
				printf("send failed!\n");
				exit(1);
			}
			memset(sstr, 0, MAXDATASIZE);
			memset(writing,0,MAXDATASIZE);
          
		}
		close(oppofd);
		close(sockfd);
		fclose(fp);

	}

	return 0;

}


int sendexit()
{
	send(oppofd, EXITTOSIG, strlen(EXITTOSIG), 0);
	return 0;
}
