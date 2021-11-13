#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char** argv)
{
   int sockfd, len;
   struct sockaddr_in server;
   char buff[128];
   if(argc !=3)
   {
      printf("usage example:  %s server_ip server_port \n",argv[0]);
	  exit(EXIT_FAILURE);
   }
   if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) <0)
   {
      perror("socket create failed\n");
	  exit(errno);
   }
   printf("create socket success\n");
   
   bzero(&server, sizeof(server));
   server.sin_family = AF_INET;
   server.sin_port = htons(atoi(argv[2]));
   if(inet_aton(argv[1], (struct in_addr *)&server.sin_addr.s_addr) == 0)
   {
      printf("%s is not the valid server ip\n",argv[1]);
	  exit(errno);
   }

   if (connect(sockfd, (struct sockaddr*) &server, sizeof(server)) == -1)
   {
      printf("connect failed \n");
	  exit(errno);
   }
   memset(buff,'\0',128);
   len = recv(sockfd, buff, 128, 0);
   printf("recv %s\n",buff);
   close(sockfd);
   printf("close\n");
   return 0;
}
