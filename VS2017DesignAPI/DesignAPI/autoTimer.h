#pragma once
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <string>

//Pimpl���÷�����ʵ�ֺ����������ķ��롣
// ͬʱ��Ҳ��ƽ̨��ش���ȫ���ŵ�ʵ���С�
class AutoTimer1
{
public:
	explicit AutoTimer1(const std::string &name);
	~AutoTimer1();
private:
	//ʹ�ö��󲻿ɸ�ֵ
	AutoTimer1(const AutoTimer1&)=delete; 
	const AutoTimer1 &operator= (const AutoTimer1 &)=delete;

	class Impl;
	std::shared_ptr<Impl> mImpl;
};