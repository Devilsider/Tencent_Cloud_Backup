#include "mylogger.h"
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main()
{
    for(int idx=0;idx<50;++idx) {
        LogInfo("this is info msg");
        LogError("this is error msg");
        LogWarn("this is warn msg");
        LogDebug("this debug msg");
    }
    return 0;
}

