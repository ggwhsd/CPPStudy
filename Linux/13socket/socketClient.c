#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#define SERVPORT 4444
#define MAXDATASIZE 256
#define STDIN 0

int main()
{
	int sockfd;
	int recvbytes;
	char buf[MAXDATASIZE];
	char name[MAXDATASIZE];
	char send_str[MAXDATASIZE];
	char client_pwd[10],msg[20];
	struct sockaddr_in serv_addr;
	fd_set rfd_set, wfd_set,efd_set;
	struct timeval timeout;
	int ret;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket failed\n");
		exit(1);
	}
	bzero(&serv_addr,sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port=htons(SERVPORT);
	inet_aton("127.0.0.1",&serv_addr.sin_addr);
	if(connect(sockfd, (struct sockaddr* )&serv_addr,sizeof(struct sockaddr)) == -1)
	{
		printf("connect failed\n");
		exit(1);

	}
	fcntl(sockfd ,F_SETFD, O_NONBLOCK);
	while(strcmp(msg,"登录成功!")!=0)
	{
		printf("请输入登录密码");
		scanf("%s",client_pwd);
		send(sockfd,client_pwd,strlen(client_pwd),0);
		recvbytes=recv(sockfd,msg,MAXDATASIZE, 0);
		msg[recvbytes]='\0';
		if(strcmp(msg,"登录成功!")!=0)
			printf("密码错误，请重新输入\n");
	}
	printf("登录成功");
	printf("聊天前请输入你的昵称:\n");
	scanf("%s",name);
	name[strlen(name)]='\0';
	printf("%s",name);
	fflush(stdout);
	send(sockfd,name,strlen(name),0);
	while(1)
	{
		FD_ZERO(&rfd_set);
		FD_ZERO(&wfd_set);
		FD_ZERO(&efd_set);
		FD_SET(STDIN,&rfd_set);
		FD_SET(sockfd,&rfd_set);
		FD_SET(sockfd,&efd_set);
		timeout.tv_sec=10;
		timeout.tv_usec=0;
		ret = select(sockfd+1, &rfd_set, &wfd_set, &efd_set, &timeout);
		if(ret ==0)
		{
			continue;
		}
		if(ret < 0)
		{
			printf("select error");
			exit(1);;
		}
		if(FD_ISSET(STDIN,&rfd_set))
		{
			fgets(send_str, 256, stdin);
			send_str[strlen(send_str)]='\0';
			if(strncmp("exit",send_str,4)==0)
			{
				printf("退出");
				close(sockfd);
				exit(0);
			}
			send(sockfd, send_str, strlen(send_str), 0);

		}
		if(FD_ISSET(sockfd, &rfd_set))
		{
			recvbytes=recv(sockfd, buf, MAXDATASIZE, 0);
			if(recvbytes==0)
			{
				close(sockfd);
				exit(0);
			}
			buf[recvbytes]='\0';
			printf("server:%s\n",buf);
			fflush(stdout);
		}
		if(FD_ISSET(sockfd, &efd_set))
		{
			close(socket);
			exit(0);

		}
	}

}	
