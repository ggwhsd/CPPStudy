# CPPStudy
using C++ 11  ,vs2017
记录开发实战中常用的一些开发知识和库的使用。

* chronoStudy.h show how to get microsecond/millisecond/second/date/time based on chrono lib.

* exceptionStudy.h shows how to use try-catch.

* libeventHello.h shows the compiled libevent.dll is in the directory : ../VS2017Project/Practice/libevent/lib32 or ../VS2017Project/Practice/libevent/lib64 [how to compile](./windows10下编译libevent（x64和x86））)

* NetBigEndStudy.h shows how to deal with bigEnd and smallEnd between computer and network.

* libeventEvbufferStudy.h shows how to construct a tcp-server which can accept\read\write with tcp-client using libevent.lib. Evbuffer is just like java.nio.BufferByte.

* Thread_condition_variable.h shows how to construct a class contains multi-Thread and how to use the notfiy/wait/unique_lock/lock_guard. 

* NLOHMANN_JSON.h is a famous json lib whose author is NLOHMANN. 
* JSONStudy.h show how to use json based on NLOHMANN_JSON.h.


* [effective c++](./effective_Cpp_50rules.md) 是当做读书笔记，结合工作中会用到的，做了记录，不会用到的，可能只是记个规则。

* [libEventProxy.h](./VS2017Project/Practice/libEventProxy.h) 简单封装了`libevent`为一个server类来使用，简化了使用方式，如下。

   ServerLib server;
   server.startByNewThread();


* [libEventProxy.h](./VS2017Project/Practice/libEventProxy.h) 封装了一个基于`socket`的client类。

   ClientLib client;
   client.SocketStart();


* [STLMap.h](./VS2017Project/Practice/STLMap.h) 使用map容器

* [STLVector.h](./VS2017Project/Practice/STLVector.h) 使用`vector`，以及内存地址变化。

