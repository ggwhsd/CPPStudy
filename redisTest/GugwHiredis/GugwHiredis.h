#pragma once
#include <string>

namespace Gugw{
	struct Gugw_redisReply
	{
		std::string replayMsg; 
		/*
		//  -1 ��ʾ����ʧ�ܣ�
		//   0 ��ʾ��ȷ
		//   4 ��ʾ����ֵΪ�ա�

		*/
		int redisError; 
	};

// ����ֵ��Ϊredis�ı�ţ������ڲ�ȷ��Ψһ��redisʵ������
int Gugw_redisConnect(const char *ip, int port);

// ����ֵ��string
Gugw_redisReply Gugw_redisCommand(int redisContext, const char* const command);


}