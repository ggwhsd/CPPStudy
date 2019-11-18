#include "stdafx.h"
#include "CMath.h"
#include "./CMathImpl.h"
CMath *c = nullptr;
CMath::CMath()
{
	impl = nullptr;
}

int CMath::Add(int a, int b)
{
	if (impl == nullptr)
		return a + b;
	else
		impl->Add(a, b);
}


CMath::~CMath()
{
	if (impl != nullptr)
	{
		delete impl;
	}
}

void CMath::Init()
{
	impl = new CMathImpl();
}

void InitCMath(CMath* child)
{
	if (child == nullptr)
		c = new CMath();
	else
		c = child;
}

void ReleaseCMath()
{
	if (c != nullptr) {
		delete c;
	}
}



int CMath_Add(int a, int b)
{
	return c->Add(a, b);
}
