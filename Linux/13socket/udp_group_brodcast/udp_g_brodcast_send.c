#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFLEN 255

void print_exit(char* con)
{
   printf("%s",con);
   exit(EXIT_FAILURE);
}
int main(int argc, char**argv)
{
    struct sockaddr_in peeraddr, myaddr;
	int sockfd;
	char recmsg[BUFLEN + 1];
	unsigned int socklen;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0){
	   print_exit("socket createing error");
	}
	socklen = sizeof(struct sockaddr_in);
	memset(&peeraddr, 0, socklen);
	peeraddr.sin_family = AF_INET;
	peeraddr.sin_port = htons(7838);
	if (argv[1]){
	  if(inet_pton(AF_INET, argv[1], &peeraddr.sin_addr) <= 0){
        print_exit("wrong group address!\n");
	}
	}
	else {
		print_exit("no group address\n");
	}
	memset(&myaddr, 0, socklen);
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8888);
	if( argv[2] )
	{
	   if(inet_pton(AF_INET, argv[2], &myaddr.sin_addr) <= 0)
	   {
	      print_exit("self ip address error!\n");
	   }
	   else
	   {
	   		myaddr.sin_addr.s_addr = INADDR_ANY;
	   }
	}
	else{
	    print_exit("self ip address null!\n");
	}
	if(bind(sockfd, (struct sockaddr*) &myaddr, sizeof(struct sockaddr_in)) == -1)
	{
	    print_exit("bind ip error!\n");
	}
	for(;;){
	    bzero(recmsg, BUFLEN + 1);
	    printf("pls enter message to send:");
	    if(fgets(recmsg, BUFLEN, stdin) == (char*) EOF)
	    	print_exit("enter nothing exit");
	   
		if(sendto(sockfd, recmsg, strlen(recmsg), 0, (struct sockaddr *)&peeraddr, sizeof(struct sockaddr_in)) < 0)
		{
		   print_exit("sendto error!\n");

		}
		printf("you have send message:%s [ local ip:%s ----> group ip:%s ]\n", recmsg,argv[2], argv[1]);
	}



}
