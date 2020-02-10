#pragma once
#pragma once

/*
*	how to use init a tcp-server based on libevent
*  how to use signal
*  how to send message to the tcp-client
*  2018-11-30 , "conn_readcb", GUGW , how to receive message from the tcp-client \ reply the message to the tcp-client \ close when received the "stop"
*/
#include "stdafx.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <thread>

#ifndef _WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/thread.h>
#include <conio.h>
#include "./chronoStudy.h"
#pragma warning(disable: 4996) // avoid strerror to be warned
	static const char MESSAGE1[] = "Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!\r\n";

	static const int PORT1 = 9995;
	bool closeflag1 = false;
	void listener_cb1(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);
	void conn_writecb1(struct bufferevent *, void *);
	void conn_readcb1(struct bufferevent *, void *);
	void conn_eventcb1(struct bufferevent *, short, void *);
	void signal_cb1(evutil_socket_t, short, void *);

	

class ServerLib
	{
	public:
		~ServerLib() { delete server; };
		ServerLib():msg("center data"),server(nullptr), base(nullptr){ };
		


		int start()
		{
			testLibeventHello();
		}
		
		void startByNewThread()
		{
			
			server = new thread(&ServerLib::testLibeventHello,this);
			server->detach();
		}



		event_base * getBase()
		{
			return base;
		}

		const string& getData()
		{
			return msg;
		}
		void setData(string s)
		{
			msg = s;
		}
	private:

		int testLibeventHello()
		{

			struct evconnlistener *listener;
			struct event *signal_event;

			struct sockaddr_in sin;
#ifdef _WIN32
			WSADATA wsa_data;
			WSAStartup(0x0201, &wsa_data);
#endif

			//使用多线程，否则，其他线程调用libevent发送数据后因为没有事件触发，导致阻塞。
#ifdef WIN32
			evthread_use_windows_threads();
#else
			evthread_use_pthreads();
#endif

			//创建事件集，用于后续所有事件
			base = event_base_new();
			if (!base) {
				fprintf(stderr, "Could not initialize libevent!\n");
				return 1;
			}
			//初始化本地网络地址
			memset(&sin, 0, sizeof(sin));
			sin.sin_family = AF_INET;
			sin.sin_port = htons(PORT1);
			//利用libevent 建立监听绑定,当有新连接来时，触发listener_cb函数
			listener = evconnlistener_new_bind(base, listener_cb1, (void *)this,
				LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
				(struct sockaddr*)&sin,
				sizeof(sin));
			if (!listener) {
				fprintf(stderr, "Could not create a listener!\n");
				return 1;
			}
			else
			{
				fprintf(stdout, "port%d!\n", sin.sin_port);
			}
			//建立信号事件，回调函数
			signal_event = evsignal_new(base, SIGINT, signal_cb1, (void *)base);
			//将信号事件加入到event_base中
			if (!signal_event || event_add(signal_event, NULL) < 0) {
				fprintf(stderr, "Could not create/add a signal event!\n");
				return 1;
			}
			//重要函数，循环监听注册的事件，若有，则调用相关的回调函数。
			int rtnCode = event_base_dispatch(base);
			//释放监听，与evconnlistener_new_bind相对应

			evconnlistener_free(listener);
			//释放事件
			event_free(signal_event);
			//释放循环监听和分发
			event_base_free(base);
#ifdef WIN32
			WSACleanup();
#endif
			printf("done%d\n",rtnCode);
			return 0;
		}

		public:
			void Shutdown()
			{
				event_base_loopbreak(base);
			}
			void SendMyMessage(string str)
			{
				bufferevent_write(bev, str.c_str(), str.length());
			}
			void SetBev(bufferevent* b)
			{
				if(bev == nullptr)
					bev = b;
				else
				{
					cout << "error bufferevent is not nullptr; can not set new bev" << endl;
				}
			}
			void ReleaseBev()
			{
				bufferevent_free(bev);
				//bev = nullptr;
			}
	private:
		thread * server;
		struct event_base *base;
		string msg;
		bufferevent* bev = nullptr;

	};

void displayIP(evutil_socket_t fd)
{
	struct sockaddr_in sa1;
	int len1 = sizeof(sa1);
	char ip[20];
	if (!getpeername(fd, (struct sockaddr *)&sa1, &len1))
	{
		inet_ntop(((struct sockaddr_in *)&sa1)->sin_family, &((struct sockaddr_in *)&sa1)->sin_addr, ip, INET_ADDRSTRLEN);
		printf("对方IP：%s ", ip);
		printf("对方PORT：%d ", ntohs(((struct sockaddr_in *)&sa1)->sin_port));
	}
}

void
listener_cb1(struct evconnlistener *listener, evutil_socket_t fd,
	struct sockaddr *sa, int socklen, void *user_data)
{
	ServerLib *user = (ServerLib*)user_data; ;
	printf("data  %s  \n", user->getData().c_str());
	struct event_base *base = (struct event_base *)user->getBase();
	struct bufferevent *bev;

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}
	
	displayIP(fd);

	bufferevent_setcb(bev, conn_readcb1, conn_writecb1, conn_eventcb1, user);
	bufferevent_enable(bev, EV_WRITE);
	bufferevent_enable(bev, EV_READ);
	bufferevent_setwatermark(bev, EV_READ, 4, 4);

	user->SetBev(bev);
	//bufferevent_disable(bev, EV_READ);
	int len = 3;
	int i = len;
	while (i > 0)
	{
		i--;
		bufferevent_write(bev, MESSAGE1, strlen(MESSAGE1));
		//printf("bufferevent_write\n");
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	printf("%s  write %f KB\n", getSystemClock_microSeconds().c_str(), strlen(MESSAGE1)*len / 1024.0);
	closeflag = false;
}

void
conn_writecb1(struct bufferevent *bev, void *user_data)
{
	ServerLib *user = (ServerLib*)user_data;
	user->setData(string("aaaaaa"));
	struct evbuffer *output = bufferevent_get_output(bev);

	if (evbuffer_get_length(output) == 0) {
		printf("%s flushed answer\n", getSystemClock_microSeconds().c_str());
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (closeflag)
			bufferevent_free(bev);
	}
	else
	{
		printf("%s flushed answer1\n", getSystemClock_microSeconds().c_str());
	}

}


void
conn_readcb1(struct bufferevent *bev, void *user_data)
{
	ServerLib *user = (ServerLib*)user_data; 
	printf("data  %s  \n", user->getData().c_str());
	char line[256];
	int n;
	evutil_socket_t fd = bufferevent_getfd(bev);

	while (n = bufferevent_read(bev, line, 255), n > 0)
	{
		line[n] = '\0';
		printf("fd=%u, read line: %s\n", fd, line);

	}
	char enter[] = "we received your message\n";
	bufferevent_write(bev, enter, strlen(enter));
	if (strcmp(line, "stop") == 0)
		closeflag = true;
}
void
conn_eventcb1(struct bufferevent *bev, short events, void *user_data)
{
	ServerLib *user = (ServerLib*)user_data; 
	printf("data  %s  \n", user->getData().c_str());
	if (events & BEV_EVENT_EOF) {
		printf("Connection closed.\n");
	}
	else if (events & BEV_EVENT_ERROR) {
		printf("Got an error on the connection: %s\n",
			strerror(errno));/*XXX win32*/
	}
	/* None of the other events can happen here, since we haven't enabled
	* timeouts */
	bufferevent_free(bev);
}
void
signal_cb1(evutil_socket_t sig, short events, void *user_data)
{
	struct event_base *base = (struct event_base *)user_data;
	struct timeval delay = { 2, 0 };

	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

	event_base_loopexit(base, &delay);
}





int tcp_connect_server(const char *server_ip, int port);
void cmd_msg_cb(evutil_socket_t fd, short events, void *arg);
void server_msg_cb(bufferevent *bev, void *arg);
void event_cb(bufferevent *bev, short event, void *arg);

class ClientLib
{
private:
	event_base * base;
public:
	void init()
	{
#ifdef _WIN32
		WSADATA wsa_data;
		WSAStartup(0x0201, &wsa_data);
#endif
		puts("init a event_base!");
		struct event_base *base; //定义一个event_base  
		base = event_base_new(); //初始化一个event_base  
		const char *x = event_base_get_method(base); //查看用了哪个IO多路复用模型，linux一下用epoll  
		printf("METHOD:%s\n", x);
		int y = event_base_dispatch(base); //事件循环。因为我们这边没有注册事件，所以会直接退出  
		event_base_free(base);  //销毁libevent  
		
#ifdef WIN32
		WSACleanup();
#endif

	}

	int SocketStart()
	{
#ifdef _WIN32
		WSADATA wsa_data;
		WSAStartup(0x0201, &wsa_data);
#endif

		int client_fd; //定义一个客户端的SOCKET    
		struct sockaddr_in server_addr; //服务器端    
		memset(&server_addr, 0, sizeof(server_addr)); //数据初始化--清零      
		server_addr.sin_family = AF_INET; //设置为IP通信      
		inet_pton(server_addr.sin_family,"127.0.0.1", &server_addr.sin_addr);//服务器IP地址      
		server_addr.sin_port = htons(9995); //服务器端口号      

		client_fd = socket(PF_INET, SOCK_STREAM, 0);
		if (client_fd < 1) {
			puts("client socket error");
			return 0;
		}
		/*将套接字绑定到服务器的网络地址上,并且连接服务器端*/
		int ret = connect(client_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
		if (ret < 0) {
			puts("client connect error!");
			return 0;
		}

		char buf[1024];
		int len = recv(client_fd, buf, 1024, 0); //等待接收服务器端的数据    
		buf[len] = '\0';
		puts(buf);

		string ss = "Hello World,saodsadoosadosa==sadsad==";
		send(client_fd, ss.c_str(), strlen(ss.c_str()), 0); //发送数据    
		memset(buf, 0, 1024);
		int len2 = recv(client_fd, buf, 1024, 0); //继续接收服务端返回的数据    
		buf[len2] = '\0';
		puts(buf);

		shutdown(client_fd, 2); //关闭socket    
	
#ifdef WIN32
		WSACleanup();
#endif
	}

	void LibEventStart()
	{
#ifdef _WIN32
		WSADATA wsa_data;
		WSAStartup(0x0201, &wsa_data);
#endif
		puts("init a event_base!");
		base = event_base_new();

		//第二个参数为-1，表示后续使用bufferevent_socket_connect再绑定socket和bufferevent
		struct bufferevent* bev = bufferevent_socket_new(base, -1,BEV_OPT_CLOSE_ON_FREE);

		struct sockaddr_in server_addr; //服务器端    
		memset(&server_addr, 0, sizeof(server_addr)); //数据初始化--清零      
		server_addr.sin_family = AF_INET; //设置为IP通信      
		inet_pton(server_addr.sin_family, "127.0.0.1", &server_addr.sin_addr);//服务器IP地址      
		server_addr.sin_port = htons(9995); //服务器端口号   
		//绑定socket和bev的关系。
		int rtn_socket =bufferevent_socket_connect(bev, (sockaddr *)&server_addr, sizeof(server_addr));
		if (rtn_socket < 0)
			cout << "bufferevent_socket_connect is fail" << endl;

		/*
		这个时linux下的监听终端输入方法

		//创建输入终端的事件，参数为与socket绑定的bufferevent*类型的bev，这样如果输入，就可以调用bev进行发送数据。
		event *ev_cmd = event_new(base, 1, EV_READ | EV_PERSIST, cmd_msg_cb, (void *)bev);
		//注册事件，第二个参数时超时，NULL为永远不超时。
		int rtn = event_add(ev_cmd, NULL);
		if (rtn <0)
			cout << "event_add is fail" << endl;
			*/

		//windows下，使用循环检查是否有输入，这个事件没有句柄，就是一个定时器。
		
		struct event *ev_cmd = event_new(base, -1, EV_PERSIST, cmd_msg_cb, (void *)bev);
		struct timeval wait_time = { 0, 100 };
		event_add(ev_cmd, &wait_time);
		


		//注册bev的事件
		bufferevent_setcb(bev, server_msg_cb, NULL, event_cb, NULL);
		bufferevent_enable(bev, EV_READ | EV_PERSIST);



		int y = event_base_dispatch(base);
		event_base_free(base);  //销毁libevent  

#ifdef WIN32
		WSACleanup();
#endif

	}
};

void cmd_msg_cb(evutil_socket_t fd, short events, void *arg) {
	char msg[1024];
	int i = 0;
	if (_kbhit())
	{
		char cInput = EOF;
		do
		{
			//读取键盘输入并回显 不用getchar 因为getchar要等用户按回车才能获取
			int nInput = (char)_getch();
			cInput = (char)nInput;
			//这里最好用putch 不用putchar 因为有时是读取到非可视化字符，如方向键
			_putch(nInput);
			msg[i] = cInput;
				i++;
		} while (_kbhit());
		msg[i] = '\0';
	}

	bufferevent *bev = (bufferevent *)arg;
	bufferevent_write(bev, msg, i);
}

void server_msg_cb(bufferevent *bev, void *arg) {
	char msg[1024];

	size_t len = bufferevent_read(bev, msg, sizeof(msg) - 1);
	msg[len] = '\0';

	printf("Recv %s from server.\n", msg);
}

void event_cb(bufferevent *bev, short event, void *arg) {
	if (event & BEV_EVENT_EOF) {
		printf("Connection closed.\n");
	}
	else if (event & BEV_EVENT_ERROR) {
		printf("Some other error.\n");
	}
	else if (event & BEV_EVENT_CONNECTED) {
		printf("Client has successfully cliented.\n");
		return;
	}

	bufferevent_free(bev);

	// free event_cmd
	// need struct as event is defined as parameter
	struct event *ev = (struct event *)arg;
	event_free(ev);
}

