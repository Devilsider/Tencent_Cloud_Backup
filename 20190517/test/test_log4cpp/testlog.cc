#include "logsimple.h"
using wd::Mylogger;
int main()
{
    Mylogger *mylogger1=Mylogger::getMylogger();
    Mylogger *mylogger2=Mylogger::getMylogger();
    mylogger1->print();
    mylogger2->print();


    for(int idx=0;idx<50;++idx){
        mylogger1->LogEmerg("this is an emerg message");//方法本身代表的就是这一条日志的级别
		mylogger1->LogFatal("this is a fatal message");
		mylogger1->LogAlert("this is an alert message");
		mylogger1->LogCrit("this is a crit message");
		mylogger1->LogWarn("this is a warn message");
		mylogger1->LogError("this is an error message");
		mylogger1->LogNotice("this is a notice message");
		mylogger1->LogInfo("this is an info message");
		mylogger1->LogDebug("this is a debug message");
    }
    
    mylogger1->destroy();
    return 0;
}

