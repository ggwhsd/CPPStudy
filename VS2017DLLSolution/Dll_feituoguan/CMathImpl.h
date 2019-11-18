#pragma once
#include "CMath.h"
class CMathImpl :
	public CMath
{
public:
	CMathImpl();
	virtual int Add(int a, int b);
	~CMathImpl();
};

