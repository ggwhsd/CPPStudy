#pragma once
#define GLOG_NO_ABBREVIATED_SEVERITIES
#define GOOGLE_GLOG_DLL_DECL
#include "logging.h"
using namespace google;


/*
	
	�ȴ�github������glog��Դ���룬����Ϊѹ��������ѹ������Ϊglogʹ�õ�cmake��������Ҫ���Լ������ϰ�װcmake
	����cmake-gui����ѡ��Դ����Ϊglog��Ŀ¼��Ŀ��λ��ΪglogĿ¼���½�һ��build-cmake,��configure��ť�������������ѡ��vs2017���������Ĭ�ϻ��⵽�����ϵ�vs�汾��
	���generate��Ĭ�����ɾ�̬�⣩��Ȼ��build-cmakeĿ¼�¾ͻ�����vs2017�Ĺ����ļ���˫���򿪹��̣��ֱ���debug��release�±��룬����glogd.lib��glog.lib������ʹ�þ�̬�⡣
	
	Ȼ���½�һ�����Թ��̣����glogd.lib��glog.lib�Լ�build-cmake/glog�����ͷ�ļ���������ȥ�����glogd.lib��glog.lib�����src/glog/log_severity.h�ļ������е���Ӳ������ǿ�����
	�ڹ��������У��ļ�����Ŀ¼����������ӵ��ļ�Ŀ¼��������Ŀ¼Ҳ����ˡ�
	�������Դ��룬��Ҫ�ڿ�ͷ���� GLOG_NO_ABBREVIATED_SEVERITIES��GOOGLE_GLOG_DLL_DECL����Ȼ�ᱨ��
	Ȼ��Ϳ���ʹ���������Բο����´��롣
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
		LOG(INFO) << "2info 2test" << "2hello 2log!";  //���һ��Info��־
													   //	LOG(WARNING) << "warning test";  //���һ��Warning��־
													   //	LOG(ERROR) << "error test";  //���һ��Error��־
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
		LOG(INFO) << "info test" << "hello log!";  //���һ��Info��־
	//	LOG(WARNING) << "warning test";  //���һ��Warning��־
	//	LOG(ERROR) << "error test";  //���һ��Error��־
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
