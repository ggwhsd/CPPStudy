# CPPStudy
using C++ 11  ,vs2017
记录开发实战中常用的一些开发知识和库的使用。

* [chronoStudy.h](./VS2017Project/Practice/chronoStudy.h) show how to get microsecond/millisecond/second/date/time based on chrono lib. 关于时间处理。

* [exceptionStudy.h](./VS2017Project/Practice/exceptionStudy.h) shows how to use try-catch.

* [libeventHello.h](./VS2017Project/Practice/libeventHello.h) shows the compiled libevent.dll is in the directory : ../VS2017Project/Practice/libevent/lib32 or ../VS2017Project/Practice/libevent/lib64 [how to compile](./windows10下编译libevent（x64和x86））)

* [NetBigEndStudy.h](./VS2017Project/Practice/NetBigEndStudy.h) shows how to deal with bigEnd and smallEnd between computer and network.

* [libeventEvbufferStudy.h](./VS2017Project/Practice/libeventEvbufferStudy.h) shows how to construct a tcp-server which can accept\read\write with tcp-client using libevent.lib. Evbuffer is just like java.nio.BufferByte.网络通信框架。

* [Thread_condition_variable.h](./VS2017Project/Practice/Thread_condition_variable.h) shows how to construct a class contains multi-Thread and how to use the notfiy/wait/unique_lock/lock_guard. 多线程之间的同步。

* [NLOHMANN_JSON.h](./VS2017Project/Practice/NLOHMANN_JSON.h) is a famous json lib whose author is NLOHMANN. 

* [JSONStudy.h](./VS2017Project/Practice/JSONStudy.h) show how to use json based on NLOHMANN_JSON.h.

* [effective c++](./effective_Cpp_50rules.md) 是当做读书笔记，结合工作中会用到的，做了记录，不会用到的，可能只是记个规则。

* [libEventProxy.h](./VS2017Project/Practice/libEventProxy.h) 简单封装了`libevent`为一个server类来使用，简化了使用方式，如下。

```cpp
   ServerLib server;
   server.startByNewThread();
```

* [libEventProxy.h](./VS2017Project/Practice/libEventProxy.h) 封装了一个基于`socket`的client类。

```cpp
   ClientLib client;
   client.SocketStart();
```

* [STLMap.h](./VS2017Project/Practice/STLMap.h) 使用map容器

* [STLVector.h](./VS2017Project/Practice/STLVector.h) 使用`vector`，以及内存地址变化。

* [logger.h](./VS2017Project/Practice/logger.h) 一个自己开发的简约日志库，实现了设置日志级别，以及线程安全记录。只要引用这个头文件，就可以使用，非常简单。

```cpp
	GGWlogger mylogger("testfile");
	mylogger.SetLevel(LOGLEVEL::LOG_DEBUG);
	mylogger.WriteLog(LOGLEVEL::LOG_INFO, "hhhhhhh");
```


