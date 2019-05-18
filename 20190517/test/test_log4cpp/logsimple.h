#ifndef __LOGSIMPLE_H__
#define __LOGSIMPLE_H__
#include <stdlib.h>
#include <stdio.h>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include<log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include<log4cpp/Priority.hh>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
using std::stringstream;
using log4cpp::PatternLayout;
using log4cpp::OstreamAppender;
using log4cpp::FileAppender;
using log4cpp::RollingFileAppender;
using log4cpp::Priority;
using log4cpp::Category;
#define logFileName "Mylogger.log"
#define rollingFileName "rollingMylogger.log"
namespace  wd{
class Mylogger{
public:
    static Mylogger *getMylogger(){
        if(NULL==_pMylogger){
            _pMylogger=new Mylogger();
            PatternLayout *patternLayout1=new PatternLayout();
            patternLayout1->setConversionPattern("%d [%p] %m%n");
           
            PatternLayout *patternLayout2=new PatternLayout();
            patternLayout2->setConversionPattern("%d [%p] %m%n");
           
            PatternLayout *patternLayout3=new PatternLayout();
            patternLayout3->setConversionPattern("%d [%p] %m%n");

            OstreamAppender *ostreamAppender=new OstreamAppender("ostreamAppender",&cout);
            ostreamAppender->setLayout(patternLayout1);

            FileAppender *fileAppender=new FileAppender("fileAppender",logFileName);
            fileAppender->setLayout(patternLayout2);

            RollingFileAppender *rollingFileAppender =new RollingFileAppender("rollingMylogger",
                                                                          rollingFileName,1024*1024,10);
            rollingFileAppender->setLayout(patternLayout3);

            _pMylogger->_myRecord.setAppender(ostreamAppender);
            _pMylogger->_myRecord.setAppender(fileAppender);
            _pMylogger->_myRecord.setAppender(rollingFileAppender);
            _pMylogger->_myRecord.setPriority(Priority::DEBUG);
        }
        return _pMylogger;
    }
    void destroy(){
        if(_pMylogger){
            delete _pMylogger;
            _pMylogger->_myRecord.shutdown();
        }
    }
    void print(){
        cout<<" _pMylogger= "<<_pMylogger<<endl;
    }
    void LogEmerg(const char * msg){
        stringstream temp;
        temp<<msg<<"("<<__FILE__<<","<<__FUNCTION__<<","<<__LINE__<<")"<<endl;
        _myRecord.emerg(temp.str());
        /* _myRecord.emerg(msg); */
    }
    void LogFatal(const char *msg){
        stringstream temp;
        temp<<msg<<"("<<__FILE__<<","<<__FUNCTION__<<","<<__LINE__<<")"<<endl;
        _myRecord.fatal(temp.str());
        /* _myRecord.fatal(msg); */
    }
    void LogAlert(const char *msg){
        stringstream temp;
        temp<<msg<<"("<<__FILE__<<","<<__FUNCTION__<<","<<__LINE__<<")"<<endl;
        _myRecord.alert(temp.str());
        /* _myRecord.alert(msg); */
    }
    void LogCrit(const char *msg){
        stringstream temp;
        temp<<msg<<"("<<__FILE__<<","<<__FUNCTION__<<","<<__LINE__<<")"<<endl;
        _myRecord.crit(temp.str());
        /* _myRecord.crit(msg); */
    }
    void LogError(const char *msg){
        stringstream temp;
        temp<<msg<<"("<<__FILE__<<","<<__FUNCTION__<<","<<__LINE__<<")"<<endl;
        _myRecord.error(temp.str());
        /* _myRecord.error(msg); */
    }
    void LogWarn(const char *msg){
        stringstream temp;
        temp<<msg<<"("<<__FILE__<<","<<__FUNCTION__<<","<<__LINE__<<")"<<endl;
        _myRecord.warn(temp.str());
         /* _myRecord.warn(msg); */
    }
    void LogNotice(const char *msg){
        stringstream temp;
        temp<<msg<<"("<<__FILE__<<","<<__FUNCTION__<<","<<__LINE__<<")"<<endl;
        _myRecord.notice(temp.str());
        /* _myRecord.notice(msg); */
    }
    void LogInfo(const char *msg){
        stringstream temp;
        temp<<msg<<"("<<__FILE__<<","<<__FUNCTION__<<","<<__LINE__<<")"<<endl;
        _myRecord.info(temp.str());
        /* _myRecord.info(msg); */
    }
    void LogDebug(const char *msg){
       stringstream temp;
        temp<<msg<<"("<<__FILE__<<","<<__FUNCTION__<<","<<__LINE__<<")"<<endl;
        _myRecord.debug(temp.str());
        /*  _myRecord.debug(msg); */
    }
  

private:
    Mylogger()
    {
    }
    ~Mylogger(){
    }
static Mylogger *_pMylogger;
static Category &_myRecord;
};
Mylogger *Mylogger::_pMylogger=NULL;
Category &Mylogger::_myRecord=Category::getRoot().getInstance("_myRecord");
}
#endif
