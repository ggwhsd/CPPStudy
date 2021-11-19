// myLibOne.cpp: 目标的源文件。
//

#include "myLibOne.h"
//#include "log.h"
#include <climits>
#include <string>
void log(std::string);
int staticLibMethod(int a, int b)
{
	log(__FUNCTION__);
	return a + b;
}
