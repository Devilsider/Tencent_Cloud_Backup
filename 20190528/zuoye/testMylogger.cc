#include "Mylogger.h"
#include <iostream>
using std::cout;
using std::endl;
int main()
{
		int number = 100;
		const char * pstr = "hello, log4cpp";
		LogInfo("this is an info message. number = %d, str = %s\n", number, pstr);
        return 0;
}

