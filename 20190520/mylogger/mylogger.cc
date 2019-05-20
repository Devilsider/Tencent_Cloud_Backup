#include "mylogger.h"
#include <iostream>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
using std::cout;
using std::endl;
#define logFileName "test.log"
#define rollLogFileName "rollTest.log"
namespace wd{

Mylogger *Mylogger::_pInstance=NULL;

Mylogger::Mylogger()
:_mylogger(Category::getRoot().getInstance("_mylogger"))
{
    PatternLayout *ptnL1=new PatternLayout();
    ptnL1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptnL2=new PatternLayout();
    ptnL2->setConversionPattern("%d %c [%p] %m%n");
    
    PatternLayout *ptnL3=new PatternLayout();
    ptnL3->setConversionPattern("%d %c [%p] %m%n");

    OstreamAppender *osa=new OstreamAppender("osa",&cout);
    osa->setLayout(ptnL1);

    FileAppender *fia=new FileAppender("fia",logFileName);
    fia->setLayout(ptnL2);

    RollingFileAppender *rolfa=new RollingFileAppender("rolfa",rollLogFileName,1024*1024,10);
    rolfa->setLayout(ptnL3);

    _mylogger.setAppender(osa);
    _mylogger.setAppender(fia);
    _mylogger.setAppender(rolfa);
    _mylogger.setPriority(Priority::DEBUG);

    cout<<"Mylogger()"<<endl;

        
}

Mylogger::~Mylogger(){
    Category::shutdown();
    cout<<"~Mylogger()"<<endl;
}

void Mylogger::error(const char *msg){
    _mylogger.error(msg);
}
void Mylogger::info(const char *msg){
    _mylogger.info(msg);
}
void Mylogger::warn(const char *msg){
    _mylogger.warn(msg);
}
void Mylogger::debug(const char *msg){
    _mylogger.debug(msg);
}
}
