#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <mutex>
#include <ctime>
#include <ratio>
#include <chrono>
#include <iomanip>
using namespace std;
/*
	自定义日志类
	WriteLog_ThreadSafe多线程安全方法
	其余均为非多线程安全方法
	
	其实在我自己的项目中，时间方法是用到另外一个自己开发的简约库，但是为了使得库可以独自使用，所以下面没有使用自己开发的库，而是重新提供了时间方法。

	由于使用的是流stream，而流本身已经是缓存，所以写入操作理论上是异步方式的，即写入到流缓存，然后程序立即往下执行，而流根据缓存是否满再写入到文件中。

*/

enum LOGLEVEL { LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_FATAL };

class GGWlogger
{

private:
	ofstream _logFile;
	string fileName;
	LOGLEVEL logLevel;
	std::mutex lock;
	void FileLogOpen(bool flag);

public:
	GGWlogger(const GGWlogger&) = delete;
	GGWlogger(const char* name);
	~GGWlogger();
	///设置日志记录级别，大于等于该级别的日志才能记录到日志中。
	void SetLevel(LOGLEVEL);
	void WriteLog_ThreadSafe(LOGLEVEL, const string&);
	void WriteLog(LOGLEVEL, const string&);
	string LevelMsg(LOGLEVEL level);
	string getSystemClock_microSeconds();
	string  getDAYHHMMSS();

	string getLogFileName();
};


typedef chrono::time_point<chrono::system_clock, chrono::microseconds> microsecond_type;
string GGWlogger::getSystemClock_microSeconds()
{

	microsecond_type tp2 = chrono::time_point_cast<chrono::microseconds>(chrono::system_clock::now());
	time_t tt;
	tt = chrono::system_clock::to_time_t(tp2);
	char timebuf[50];
	tm ltm;
	localtime_s(&ltm, &tt);
	strftime(timebuf, 30, "%F %R:%S", &ltm);
	char mircostr[8];
	mircostr[7] = '\0';
	sprintf_s(mircostr, ".%06d", static_cast<int>(tp2.time_since_epoch().count() % (1000000)));
	string str(timebuf);
	str.append(mircostr);
	return str;
}

string GGWlogger::getDAYHHMMSS()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	char timebuf[31];
	strftime(timebuf, 30, "DAY%j_%F_%H_%M", ltm);
	string strTime(timebuf);
	return strTime;
}

inline string GGWlogger::getLogFileName()
{
	return fileName;
}

GGWlogger::GGWlogger(const char* name)
{
	logLevel = LOGLEVEL::LOG_INFO;
	fileName.append(name);
	FileLogOpen(true);
}

GGWlogger::~GGWlogger()
{
	_logFile.flush();
	FileLogOpen(false);
	
}

void GGWlogger::SetLevel(LOGLEVEL level)
{
	logLevel = level;
}

void GGWlogger::FileLogOpen(bool flag)
{
	char filePath[100] = { '\0' };
	sprintf(filePath, "%s_%s.log", fileName.c_str(), getDAYHHMMSS().c_str());
	if (flag) {
		_logFile.open(filePath, std::ios::out);
		_logFile << "log begin" << endl;
	}
	else
	{
		_logFile.close();
	}
}

void GGWlogger::WriteLog_ThreadSafe(LOGLEVEL level, const string& str)
{
	if (level >= logLevel)
	{
		lock.lock();
		_logFile << getSystemClock_microSeconds() << " " << LevelMsg(level) << str.c_str() << endl;
		lock.unlock();
	}
}

void GGWlogger::WriteLog(LOGLEVEL level, const string & str)
{
	if (level >= logLevel)
	{
		if (_logFile.good())
		{

			_logFile << getSystemClock_microSeconds() << " " << LevelMsg(level) << str.c_str() << endl;;

		}
	}
}

string GGWlogger::LevelMsg(LOGLEVEL level)
{
	switch (level)
	{
		case LOGLEVEL::LOG_DEBUG:
		{
			return " [DEBUG] ";
		}
		break;
		case LOGLEVEL::LOG_INFO:
		{
			return " [INFO] ";
		}
		break;
		case LOGLEVEL::LOG_WARNING:
		{
			return " [WARNING] "; 
		}
		break;
		case LOGLEVEL::LOG_ERROR:
		{
			return " [ERROR] "; 
		}
		break;
		case LOGLEVEL::LOG_FATAL:
		{
			return " [FATAL] "; 
		}
		break;
		default:
		{
			return " [DEBUG] "; 
		}
		break;
	}
}
