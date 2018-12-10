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

#include "./chronoStudy.h"

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
			//�����¼��������ں��������¼�
			base = event_base_new();
			if (!base) {
				fprintf(stderr, "Could not initialize libevent!\n");
				return 1;
			}
			//��ʼ�����������ַ
			memset(&sin, 0, sizeof(sin));
			sin.sin_family = AF_INET;
			sin.sin_port = htons(PORT1);
			//����libevent ����������,������������ʱ������listener_cb����
			listener = evconnlistener_new_bind(base, listener_cb1, (void *)this,
				LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
				(struct sockaddr*)&sin,
				sizeof(sin));
			if (!listener) {
				fprintf(stderr, "Could not create a listener!\n");
				return 1;
			}
			//�����ź��¼����ص�����
			signal_event = evsignal_new(base, SIGINT, signal_cb1, (void *)base);
			//���ź��¼����뵽event_base��
			if (!signal_event || event_add(signal_event, NULL) < 0) {
				fprintf(stderr, "Could not create/add a signal event!\n");
				return 1;
			}
			//��Ҫ������ѭ������ע����¼������У��������صĻص�������
			event_base_dispatch(base);
			//�ͷż�������evconnlistener_new_bind���Ӧ

			evconnlistener_free(listener);
			//�ͷ��¼�
			event_free(signal_event);
			//�ͷ�ѭ�������ͷַ�
			event_base_free(base);

			printf("done\n");
			return 0;
		}

	private:
		thread * server;
		struct event_base *base;
		string msg;

	};


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
	bufferevent_setcb(bev, conn_readcb1, conn_writecb1, conn_eventcb1, user);
	bufferevent_enable(bev, EV_WRITE);
	bufferevent_enable(bev, EV_READ);
	bufferevent_setwatermark(bev, EV_READ, 4, 4);
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






class ClientLib
{
public:
	void init()
	{
#ifdef _WIN32
		WSADATA wsa_data;
		WSAStartup(0x0201, &wsa_data);
#endif
		puts("init a event_base!");
		struct event_base *base; //����һ��event_base  
		base = event_base_new(); //��ʼ��һ��event_base  
		const char *x = event_base_get_method(base); //�鿴�����ĸ�IO��·����ģ�ͣ�linuxһ����epoll  
		printf("METHOD:%s\n", x);
		int y = event_base_dispatch(base); //�¼�ѭ������Ϊ�������û��ע���¼������Ի�ֱ���˳�  
		event_base_free(base);  //����libevent  
		


	}

	int SocketStart()
	{
#ifdef _WIN32
		WSADATA wsa_data;
		WSAStartup(0x0201, &wsa_data);
#endif

		int client_fd; //����һ���ͻ��˵�SOCKET    
		struct sockaddr_in server_addr; //��������    
		memset(&server_addr, 0, sizeof(server_addr)); //���ݳ�ʼ��--����      
		server_addr.sin_family = AF_INET; //����ΪIPͨ��      
		inet_pton(server_addr.sin_family,"127.0.0.1", &server_addr.sin_addr);//������IP��ַ      
		server_addr.sin_port = htons(9995); //�������˿ں�      

		client_fd = socket(PF_INET, SOCK_STREAM, 0);
		if (client_fd < 1) {
			puts("client socket error");
			return 0;
		}
		/*���׽��ְ󶨵��������������ַ��,�������ӷ�������*/
		int ret = connect(client_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
		if (ret < 0) {
			puts("client connect error!");
			return 0;
		}

		char buf[1024];
		int len = recv(client_fd, buf, 1024, 0); //�ȴ����շ������˵�����    
		buf[len] = '\0';
		puts(buf);

		string ss = "Hello World,saodsadoosadosa==sadsad==";
		send(client_fd, ss.c_str(), strlen(ss.c_str()), 0); //��������    
		memset(buf, 0, 1024);
		int len2 = recv(client_fd, buf, 1024, 0); //�������շ���˷��ص�����    
		buf[len2] = '\0';
		puts(buf);

		shutdown(client_fd, 2); //�ر�socket    
	

	}
};