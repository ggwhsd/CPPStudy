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
#pragma warning(disable: 4996) // avoid strerror to be warned
static const char MESSAGE[] = "Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!Hello, World!\r\n";

static const int PORT = 9995;
bool closeflag = false;
static void listener_cb(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);
static void conn_writecb(struct bufferevent *, void *);
static void conn_readcb(struct bufferevent *, void *);
static void conn_eventcb(struct bufferevent *, short, void *);
static void signal_cb(evutil_socket_t, short, void *);

static int testLibeventEvbuffer(int argc, char **argv)
{
	struct event_base *base;
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
	sin.sin_port = htons(PORT);
	//����libevent ����������,������������ʱ������listener_cb����
	listener = evconnlistener_new_bind(base, listener_cb, (void *)base,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
		(struct sockaddr*)&sin,
		sizeof(sin));
	if (!listener) {
		fprintf(stderr, "Could not create a listener!\n");
		return 1;
	}
	//�����ź��¼����ص�����
	signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);
	//���ź��¼����뵽event_base��
	if (!signal_event || event_add(signal_event, NULL)<0) {
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

static void
listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
	struct sockaddr *sa, int socklen, void *user_data)
{
	struct event_base *base = (struct event_base *)user_data;
	struct bufferevent *bev;
	struct evbuffer *buf = evbuffer_new();
	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}
	bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, buf);
	bufferevent_enable(bev, EV_WRITE);
	bufferevent_enable(bev, EV_READ);
	bufferevent_setwatermark(bev, EV_READ, 0, 0);
	//bufferevent_disable(bev, EV_READ);
	int len = 3;
	int i = len;
	while (i>0)
	{
		i--;
		//bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
		evbuffer_add(buf, MESSAGE, strlen(MESSAGE));
		bufferevent_write_buffer(bev, buf);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	printf("%s  write %f KB\n", getSystemClock_microSeconds().c_str(), strlen(MESSAGE)*len / 1024.0);
	closeflag = false;
}

static void
conn_writecb(struct bufferevent *bev, void *user_data)
{
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


static void
conn_readcb(struct bufferevent *bev, void *user_data)
{

	struct evbuffer *buf = (struct evbuffer *)user_data;
	char line[256];
	int n;
	evutil_socket_t fd = bufferevent_getfd(bev);
	while (n = bufferevent_read(bev, line, 255), n > 0)
	{
		line[n] = '\0';
		//printf("fd=%u, read line: %s\n", fd, line);
		printf("%s",  line);
	}
	//bufferevent_write(bev, enter, strlen(enter));
	evbuffer_add(buf, line, strlen(line));
	const char *separate = "\r\n";
	struct evbuffer_ptr ptr = evbuffer_search(buf, separate, strlen(separate), 0);
	if (ptr.pos != -1) {
		
		bufferevent_write_buffer(bev, buf); //ʹ��buffer�ķ�ʽ������  
		ptr = evbuffer_search(buf, "stop", strlen("stop"), 0);
		if (ptr.pos != -1)
			closeflag = true;
	}
	else
	{
		//printf("%d",evbuffer_get_length(buf));
	}

	
	
}
static void
conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
	if (events & BEV_EVENT_EOF) {
		printf("Connection closed.\n");
	}
	else if (events & BEV_EVENT_ERROR) {
		printf("Got an error on the connection: %s\n",
			strerror(errno));/*XXX win32*/
	}
	/* None of the other events can happen here, since we haven't enabled
	* timeouts */
	struct evbuffer *buf = (struct evbuffer *)user_data;
	evbuffer_free(buf);
	bufferevent_free(bev);
}

static void
signal_cb(evutil_socket_t sig, short events, void *user_data)
{
	struct event_base *base = (struct event_base *)user_data;
	struct timeval delay = { 2, 0 };

	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

	event_base_loopexit(base, &delay);

}
