#pragma once
class __declspec(dllexport) CMath
{
public:
	CMath();
	virtual int Add(int a, int b);
	virtual ~CMath();
	void Init();
private:
	CMath * impl = nullptr;
};
//����̳�,����Ϊ��һ��������ʹ�����Ǳ߼̳еķ�ʽ,����ÿ��ֻ����һ����ʾ��
void InitCMath(CMath* child);
void ReleaseCMath();
int CMath_Add(int,int);

//�ڲ����ɣ����ṩ�ⲿ���ɵķ�ʽ,ֱ�ӵ������Init���������Դ��������ʵ����


