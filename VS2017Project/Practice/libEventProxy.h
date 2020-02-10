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

			//ʹ�ö��̣߳����������̵߳���libevent�������ݺ���Ϊû���¼�����������������
#ifdef WIN32
			evthread_use_windows_threads();
#else
			evthread_use_pthreads();
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
			else
			{
				fprintf(stdout, "port%d!\n", sin.sin_port);
			}
			//�����ź��¼����ص�����
			signal_event = evsignal_new(base, SIGINT, signal_cb1, (void *)base);
			//���ź��¼����뵽event_base��
			if (!signal_event || event_add(signal_event, NULL) < 0) {
				fprintf(stderr, "Could not create/add a signal event!\n");
				return 1;
			}
			//��Ҫ������ѭ������ע����¼������У��������صĻص�������
			int rtnCode = event_base_dispatch(base);
			//�ͷż�������evconnlistener_new_bind���Ӧ

			evconnlistener_free(listener);
			//�ͷ��¼�
			event_free(signal_event);
			//�ͷ�ѭ�������ͷַ�
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
		printf("�Է�IP��%s ", ip);
		printf("�Է�PORT��%d ", ntohs(((struct sockaddr_in *)&sa1)->sin_port));
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
		struct event_base *base; //����һ��event_base  
		base = event_base_new(); //��ʼ��һ��event_base  
		const char *x = event_base_get_method(base); //�鿴�����ĸ�IO��·����ģ�ͣ�linuxһ����epoll  
		printf("METHOD:%s\n", x);
		int y = event_base_dispatch(base); //�¼�ѭ������Ϊ�������û��ע���¼������Ի�ֱ���˳�  
		event_base_free(base);  //����libevent  
		
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

		//�ڶ�������Ϊ-1����ʾ����ʹ��bufferevent_socket_connect�ٰ�socket��bufferevent
		struct bufferevent* bev = bufferevent_socket_new(base, -1,BEV_OPT_CLOSE_ON_FREE);

		struct sockaddr_in server_addr; //��������    
		memset(&server_addr, 0, sizeof(server_addr)); //���ݳ�ʼ��--����      
		server_addr.sin_family = AF_INET; //����ΪIPͨ��      
		inet_pton(server_addr.sin_family, "127.0.0.1", &server_addr.sin_addr);//������IP��ַ      
		server_addr.sin_port = htons(9995); //�������˿ں�   
		//��socket��bev�Ĺ�ϵ��
		int rtn_socket =bufferevent_socket_connect(bev, (sockaddr *)&server_addr, sizeof(server_addr));
		if (rtn_socket < 0)
			cout << "bufferevent_socket_connect is fail" << endl;

		/*
		���ʱlinux�µļ����ն����뷽��

		//���������ն˵��¼�������Ϊ��socket�󶨵�bufferevent*���͵�bev������������룬�Ϳ��Ե���bev���з������ݡ�
		event *ev_cmd = event_new(base, 1, EV_READ | EV_PERSIST, cmd_msg_cb, (void *)bev);
		//ע���¼����ڶ�������ʱ��ʱ��NULLΪ��Զ����ʱ��
		int rtn = event_add(ev_cmd, NULL);
		if (rtn <0)
			cout << "event_add is fail" << endl;
			*/

		//windows�£�ʹ��ѭ������Ƿ������룬����¼�û�о��������һ����ʱ����
		
		struct event *ev_cmd = event_new(base, -1, EV_PERSIST, cmd_msg_cb, (void *)bev);
		struct timeval wait_time = { 0, 100 };
		event_add(ev_cmd, &wait_time);
		


		//ע��bev���¼�
		bufferevent_setcb(bev, server_msg_cb, NULL, event_cb, NULL);
		bufferevent_enable(bev, EV_READ | EV_PERSIST);



		int y = event_base_dispatch(base);
		event_base_free(base);  //����libevent  

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
			//��ȡ�������벢���� ����getchar ��ΪgetcharҪ���û����س����ܻ�ȡ
			int nInput = (char)_getch();
			cInput = (char)nInput;
			//���������putch ����putchar ��Ϊ��ʱ�Ƕ�ȡ���ǿ��ӻ��ַ����緽���
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

