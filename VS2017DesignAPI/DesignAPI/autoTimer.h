#pragma once
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <string>

//Pimpl惯用法，将实现和声明完美的分离。
// 同时，也将平台相关代码全部放到实现中。
class AutoTimer1
{
public:
	explicit AutoTimer1(const std::string &name);
	~AutoTimer1();
private:
	//使得对象不可赋值
	AutoTimer1(const AutoTimer1&)=delete; 
	const AutoTimer1 &operator= (const AutoTimer1 &)=delete;

	class Impl;
	std::shared_ptr<Impl> mImpl;
};