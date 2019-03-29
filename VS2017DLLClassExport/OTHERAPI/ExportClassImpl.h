#pragma once

#include "b.h"

class ExportImpl : public IExport
{
public:
	virtual void Hi();
	virtual void Test();
	virtual void Release();
	~ExportImpl();
private:
};