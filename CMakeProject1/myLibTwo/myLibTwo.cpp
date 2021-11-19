// myLibTwo.cpp: 目标的源文件。
//

#include "myLibTwo.h"
#include <climits>
#include <string>
#include "../myLibOne/log.h"

int DynamicLibMethod(int a, int b)
{
	
	log(__FUNCTION__);
	return a + b;
}
