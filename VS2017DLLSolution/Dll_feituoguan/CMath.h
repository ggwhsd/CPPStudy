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
//方便继承,以下为第一种在其他使用者那边继承的方式,而且每次只能用一个类示例
void InitCMath(CMath* child);
void ReleaseCMath();
int CMath_Add(int,int);

//内部集成，不提供外部集成的方式,直接调用类的Init方法，可以创建多个类实例。


