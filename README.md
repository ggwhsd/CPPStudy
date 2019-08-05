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

* [effective c++](./effective_Cpp_rules.md) 是当做《effective c++》读书笔记，结合工作中会用到的，做了记录，不会用到的，可能只是记个规则。同时里面也补充了《more effective c++》中的一些规则。

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
	mylogger.WriteLog( "hhhhhhh", LOGLEVEL::LOG_INFO);
	mylogger.LogInfo("hhhhhhh");
	mylogger.WriteLog("hhhhhhh");
	
```

* [xmlStudy.h](./VS2017Project/Practice/xmlStudy.h) 如何使用`tinyxml2`库进行xml文件的读写使用。

* [Cpp11_Function_Study.h](./VS2017Project/Practice/Cpp11_Function_Study.h) 介绍了C++11中引入的Function，相当于是以前C语言中的函数指针，但是可以封装很好，可以分装各种函数。
也介绍了右值引用&&，这个也是C++11中新引入的机制，对于提升内存使用效率很有用。
新增了bind的使用方式，这样就可以使用同一个function，来对应参数相同，返回值相同的不同普通函数，不同类对象，以及不同类成员函数，从而可以实现多种映射方式。简直很棒。

* [ThreadsWaitNotifyManager.h](./VS2017Project/Practice/ThreadsWaitNotifyManager.h) 用于多线程之间通信的一个类。

* [libeventTimerStudy.h](./VS2017Project/Practice/libeventTimerStudy.h) 定时器的使用，基于libevent中的定时器进行了封装，使用时候只要创建Timer类的SetTimer做初始化，调用addTimer方法添加定时器以及方法的回调。
在使用多线程时，一定要有下面这条语句，否则多线程环境里面，定时器的时间是不准的。evthread_use_windows_threads()，我个人台式机上，多线程，定时设置300毫秒，基本误差20毫秒以内，定时设置900毫秒，误差还是20毫秒以内。

# DLL

* VS2017DLLSolution 里面是有建立托管和非托管dll的示例。

* [VS2017DLLClassExport](./VS2017DLLClassExport/) 是介绍如何导出类的方法，
分为两种,第一种直接导出实现类，头文件包含类中所有的方法声明。
第二种导出虚类接口，头文件只包含接口不包含实现类的声明。
2019-4-16 新增，线程通信类的自定义开发的库。

* [循环队列的实现](./VS2017Project/Practice/CircleVector.h)

* [指针和类之间的关系](./VS2017Project/Practice/pointerToMember.h)

* [Math基础](./VS2017Project/Practice/mathTest.h)

* [numeric_limits最大值最小值](./VS2017Project/Practice/mathTest.h)

* [va_args多参数使用](./VS2017Project/Practice/va_listStudy.h)

* [shared_ptr和auto_ptr](./VS2017Project/Practice/shardPtrStudy.h)

* [future,async异步线程](./VS2017Project/Practice/asyncFutureStudy.h)

* [future,promise](./VS2017Project/Practice/future_promise_test.h)

* [future,promise,packaged_task](./VS2017Project/Practice/packagedTaskStudy.h)

* [谷歌的glog日志库的使用](./VS2017Project/Practice/glogStudy.h)

* glog日志工程，基于32和64的vs2017工程解决方案[工程](./glog-master)
