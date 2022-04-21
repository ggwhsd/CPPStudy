#pragma once
#define GLOG_NO_ABBREVIATED_SEVERITIES
#define GOOGLE_GLOG_DLL_DECL
#include "logging.h"
using namespace google;


/*
	
	先从github上下载glog的源代码，下载为压缩包，解压缩，因为glog使用的cmake，所以需要在自己电脑上安装cmake
	启动cmake-gui程序，选择源代码为glog的目录，目标位置为glog目录下新建一个build-cmake,在configure按钮点击，弹出窗口选择vs2017（这个都是默认会检测到电脑上的vs版本）
	点击generate（默认生成静态库），然后到build-cmake目录下就会生成vs2017的工程文件，双击打开工程，分别在debug和release下编译，生成glogd.lib和glog.lib，这里使用静态库。
	
	然后新建一个测试工程，添加glogd.lib和glog.lib以及build-cmake/glog下面的头文件到工程中去，添加glogd.lib和glog.lib，添加src/glog/log_severity.h文件。所有的添加操作都是拷贝。
	在工程属性中，文件引入目录包含以上添加的文件目录，库引用目录也是如此。
	创建测试代码，需要在开头加上 GLOG_NO_ABBREVIATED_SEVERITIES和GOOGLE_GLOG_DLL_DECL，不然会报错。
	然后就可以使用啦，可以参考如下代码。
*/


#ifdef _DEBUG
	#pragma comment(lib, "glogd.lib")
#else
#pragma comment(lib, "glog.lib")

#endif // DEBUG


void testGlog2()
{
	char str[20] = "hello log!";
	int i = 100000;
	while (i > 0) {
		//	LOG(INFO) << str;
		LOG(INFO) << "2info 2test" << "2hello 2log!";  //输出一个Info日志
													   //	LOG(WARNING) << "warning test";  //输出一个Warning日志
													   //	LOG(ERROR) << "error test";  //输出一个Error日志
		i--;
	}
}
void testGlog()
{
	// Start google log system:
	FLAGS_log_dir = "E:\\logs";
	google::InitGoogleLogging("loglog");
	google::SetLogDestination(google::GLOG_INFO, "E:\\logs\\INFO_");
	google::SetStderrLogging(google::GLOG_FATAL);
	google::SetLogFilenameExtension("log_");
	FLAGS_colorlogtostderr = true;  // Set log color
	FLAGS_logbufsecs = 0;  // Set log output speed(s)
	FLAGS_max_log_size = 1024;  // Set max log file size
	FLAGS_stop_logging_if_full_disk = true;  // If disk is full

	thread *t = new thread(testGlog2);
	
	char str[20] = "hello log!";
	int i = 100000;
	while (i > 0) {
	//	LOG(INFO) << str;
		LOG(INFO) << "info test" << "hello log!";  //输出一个Info日志
	//	LOG(WARNING) << "warning test";  //输出一个Warning日志
	//	LOG(ERROR) << "error test";  //输出一个Error日志
		i--;
	}
	t->join();

	google::ShutdownGoogleLogging();

}

class MyLogSink : public LogSink
{
public:
	virtual void send(LogSeverity severity, const char* full_filename,
		const char* base_filename, int line,
		const struct ::tm* tm_time,
		const char* message, size_t message_len)
	{
		cout << __FUNCTION__ << " " << severity << " " << full_filename << " " << base_filename << " " << line << " " << tm_time->tm_hour << ":" << tm_time->tm_sec << " " << message << endl;
	}


};


void testGlogSink()
{
	google::InitGoogleLogging("loglog");
	google::SetLogDestination(google::GLOG_INFO, "G:\\temp\\INFO_");
	google::SetStderrLogging(google::GLOG_FATAL);
	google::SetLogFilenameExtension("log_");
	FLAGS_colorlogtostderr = true;  // Set log color
	FLAGS_logbufsecs = 0;  // Set log output speed(s)
	FLAGS_max_log_size = 1024;  // Set max log file size
	FLAGS_stop_logging_if_full_disk = true;  // If disk is full
	MyLogSink mySink;
	LOG_TO_SINK(&mySink, INFO) << " test my Sink";
	LOG(INFO) << " test file log";
	google::ShutdownGoogleLogging();
}
