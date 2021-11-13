#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/param.h>
#include <sys/syslog.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 4096

int main(int argc, char **argv)
{
   struct sockaddr *cliaddr;
   char buff[MAXLINE];
   time_t ticks;
   ticks = time(NULL);
   snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
   write(0, buff, strlen(buff));   //for xinetd call this service program， it will redirect 0 output to socket
   close(0);
   exit(0);
}


