#pragma once
#ifdef NAIVEAPPROACH_EXPORTS
#define NAIVEAPPROACH_API __declspec(dllexport)
#else
#define NAIVEAPPROACH_API __declspec(dllimport)
#endif

//基类也必须导出，否则警告：
class  NAIVEAPPROACH_API CBase
{
public:
	void Test();
private:
	int m_j;
};

//也必须导出
class NAIVEAPPROACH_API CDate
{
public:
	void Test2();
private:
	int m_k;
};

class NAIVEAPPROACH_API CNaiveApproach : public CBase
{
public:
	CNaiveApproach(int i = 0);
	// TODO: add your methods here.
	void Func();
private:
	int m_iwuyg;
	CDate m_dobj;
};
