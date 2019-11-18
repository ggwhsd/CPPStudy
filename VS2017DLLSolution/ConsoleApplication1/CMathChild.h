#pragma once

#include "CMath.h"


void InitCMath(CMath* child);
void ReleaseCMath();
int CMath_Add(int, int);

class CMathChild : public CMath
{
public:
	CMathChild();
	virtual int Add(int a, int b);
	virtual ~CMathChild();
};

