
// this is a server socket example with sigpipe handler. 
// so the program will not destroy by OS when the client close the socket.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include <unistd.h>
#include <arpa/inet.h>

void handler(int sig)
{
   printf("sig = %d\n",sig);
}
void print_exit(char *con)
{
   printf("%s",con);
   exit(EXIT_FAILURE);
}
int main(int argc, char *argv[])
{
   int pid, bytes;
   int sockfd , new_fd;
   socklen_t len;
   struct sockaddr_in my_addr, their_addr;
   char buffer[128];
   //set signal to handler function
   signal(SIGPIPE, handler);
   if(( sockfd = socket(AF_INET, SOCK_STREAM, 0)) ==-1)
   {
      print_exit("create socket failed\n");
   }
   bzero(&my_addr, sizeof(my_addr));
   my_addr.sin_family = AF_INET;
   //get port
   printf("port :%s \n", argv[2]);
   my_addr.sin_port = htons(atoi(argv[2]));
   //get ip address
   if (inet_aton(argv[1], (struct in_addr*) &my_addr.sin_addr.s_addr)==0)
   {
      print_exit("ip address convert failed");
   }
   printf("get local ip address\n");
   if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1)
   {
      print_exit("bind failed");
   }
   printf("bind address and port success\n");
   if(listen(sockfd, 5) == -1)
   {
      print_exit("listen failed");
   }
   printf("listen success\n");
   len = sizeof(struct sockaddr);
   while(1)
   {
      printf("server is waiting for a client connect\n");
	  if ((new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &len)) == -1)
	  {
	     print_exit("accept\n");
	  }
	  else
	  {
	     printf("server: got connection from %s, port %d\n",
		       inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port));
	     while(1)
		 {
		    bzero(buffer, 128);
			printf("pls send message to send:");
			fgets(buffer, 128, stdin);
			if(!strncasecmp(buffer, "quit", 4))
			{
			   printf("quit this socket connect\n");
			   break;
			}
			//write send message without buffer memory. while method "send" has buffer.
			bytes = write(new_fd, buffer, strlen(buffer));
			if(bytes<0)
			{
			   printf("send fail, errno [%d], err msg [%s]\n",errno, strerror(errno));
			   //you should know the different between close and shutdown.
			   close(new_fd);
			   break;
			}
			else
			{
			   printf("message:%s\t success",buffer);
			}

		 }
	  }
   }
   //close the listen socket.
   close(sockfd);
   return 0;


















}
