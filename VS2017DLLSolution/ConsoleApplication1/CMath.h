#pragma once
class CMath
{
public:
	CMath();
	virtual int Add(int a, int b);
	virtual ~CMath();
	void Init();
private:
	CMath * impl = nullptr;
};


