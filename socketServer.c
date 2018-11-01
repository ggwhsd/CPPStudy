//socket server 使用select实现非阻塞方式，之前的socketserverandclient里面是使用了多线程方式来实现主程序非阻塞
//
//
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
#define BACKLOG 10
#define STDIN 0
#define MAXDATASIZE 256
int main(void)
{
	FILE *fp;
	int sockfd,client_fd;
	int sin_size;
	struct sockaddr_in my_addr, remote_addr;
	char buf[256];//聊天用
	char buff[256];//用户名用
	char send_str[256];
	char choice;
	int recvbytes;
	fd_set rfd_set, wfd_set, efd_set;
	struct timeval timeout; //select 最大允许时间
	int ret; //select 结果
	char serv_pwd[10],serv_repwd[10];
	char trial_pwd[10];
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket error");
		exit(1);
	}

	bzero(&my_addr,sizeof(struct sockaddr_in));
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(SERVPORT);
	inet_aton("127.0.0.1", &my_addr.sin_addr);
	if(bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1)
	{
		printf("bind");
		exit(1);
	}
	if(listen(sockfd, BACKLOG)==-1)
	{
		printf("listen");
		exit(1);
	}
	printf("请先输入密码：\n请输入");
	scanf("%s",serv_pwd);
	printf("请再次输入密码：");
	scanf("%s",serv_repwd);
	while(strcmp(serv_pwd, serv_repwd)!=0)
	{
		printf("两次输入的密码不一样，请重试\n 请输入");
		scanf("%s",serv_pwd);
		printf("请确认密码");
		scanf("%s",serv_repwd);
	}
	printf("密码设置成功!\n");
	sin_size = sizeof(struct sockaddr_in);
	if((client_fd = accept(sockfd, (struct sockaddr*)&remote_addr,&sin_size))==-1)
	{
		printf("accept");
		exit(1);
	}
	//设置为非阻塞模式
	fcntl(client_fd,F_SETFD,O_NONBLOCK);
	recvbytes = recv(client_fd,trial_pwd,MAXDATASIZE, 0);
	trial_pwd[recvbytes]='\0';
	while(strcmp(trial_pwd,serv_pwd)!=0)
	{
		send(client_fd,"登陆密码错误，请重试",sizeof("登录密码错误，请重试"),0);
		recvbytes=recv(client_fd,buff,MAXDATASIZE,0);
		trial_pwd[recvbytes]='\0';
	}
		send(client_fd,"登录成功!",sizeof("登录成功!"),0);
		recvbytes=recv(client_fd,buff,MAXDATASIZE, 0);
		
		buff[recvbytes]='\0';
		printf("用户%s成功登录",buff);
		fflush(stdout);
		if((fp=fopen("name.txt","a+"))==NULL)
		{
			exit(1);	
		}
		fprintf(fp,"%s\n",buff);
		while(1)
		{
			FD_ZERO(&rfd_set);
			FD_ZERO(&wfd_set);
			FD_ZERO(&efd_set);
			FD_SET(STDIN, &rfd_set);
			FD_SET(client_fd, &rfd_set);
			FD_SET(client_fd, &wfd_set);
			FD_SET(client_fd, &efd_set);
			timeout.tv_sec = 10;
			timeout.tv_usec = 0;
			ret = select(client_fd+1, &rfd_set, &wfd_set, &efd_set, &timeout);
            if(ret == 0)
			{
				continue;
			}
			if(ret<0)//timeout
			{
				printf("select");
				exit(1);
			}
			if(FD_ISSET(STDIN,&rfd_set))
			{
				fgets(send_str, 256, stdin);
				send_str[strlen(send_str)]='\0';
				if(strncmp("exit",send_str,4)==0)
				{
					printf("确定要退出么\n?");
					scanf("%c",&choice);
					if(choice == 'y'||choice == 'Y')
					{
						close(client_fd);
						close(socket);
						exit(0);
					}

				}
				send(client_fd,send_str,strlen(send_str),0);

				
			}
			if(FD_ISSET(client_fd, &rfd_set))
			{
				recvbytes=recv(client_fd,buf,MAXDATASIZE,0);
				if(recvbytes == 0)
				{
					close(client_fd);
					close(sockfd);
					exit(0);

				}
				buf[recvbytes]='\0';
				printf("%s:%s\n",buff,buf);
				printf("server:");
				fflush(stdout);
			}
			if(FD_ISSET(client_fd, &efd_set))
			{
				close(sockfd);	
				close(client_fd);
				exit(0);
			}
		}
	return 0;
}
