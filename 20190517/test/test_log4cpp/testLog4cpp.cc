#include<log4cpp/Category.hh>
#include<log4cpp/Priority.hh>
#include<log4cpp/PatternLayout.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/FileAppender.hh>
#include<log4cpp/RollingFileAppender.hh>

#include <iostream>
using std::cout;
using std::endl;
using namespace log4cpp;

int main()
{
    PatternLayout *patternlayout1=new PatternLayout();
    patternlayout1->setConversionPattern("%d [%p] %m%n");
    PatternLayout *patternlayout2=new PatternLayout();
    patternlayout2->setConversionPattern("%d [%p] %m%n");
    PatternLayout *patternlayout3=new PatternLayout();
    patternlayout3->setConversionPattern("%d [%p] %m%n");

    OstreamAppender *ostreamAppender=
        new OstreamAppender("ostreamAppender",&cout);
    ostreamAppender->setLayout(patternlayout1);
    
    FileAppender * fileAppender=
        new FileAppender("fileAppender","test.log");
    fileAppender->setLayout(patternlayout2);

    RollingFileAppender *rollingFileAppender=
        new RollingFileAppender("rollingFileAppender","rolltest.log",
                                1024,10);
    rollingFileAppender->setLayout(patternlayout3);

    Category &myrecord=Category::getRoot().getInstance("myrecord");
    myrecord.setAppender(ostreamAppender);
    myrecord.setAppender(fileAppender);
    myrecord.setAppender(rollingFileAppender);
    myrecord.setPriority(Priority::DEBUG);

    for(int idx=0;idx!=50;++idx){
        myrecord.emerg("this is emerg messages");
        myrecord.fatal("this is fatal messages");
        myrecord.alert("this is alert messages");
        myrecord.crit("this is crit messages");
        myrecord.warn("this is warn messages");
        myrecord.notice("this is notice messages");
        myrecord.error("this is error messages");
        myrecord.info("this is error messages");
        myrecord.debug("this is debug messages");
    }


    Category::shutdown();
    return 0;
}

