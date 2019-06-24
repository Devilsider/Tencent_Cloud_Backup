#include "MyReaderXML.h"
#include "PageLib.h"
#include "tinyxml2.h"
#include <iostream>


namespace wd
{

PageLib::PageLib(DirScanner &dirscanner)
:_dirScanner(dirscanner)
{}

void PageLib::createFormatPageLib()
{   
    cout<<"111"<<endl;
    MyReaderXML readerXML;
    auto  vec = _dirScanner.getFile();
    cout<<"222"<<endl;
    for(auto iter = vec.begin();iter!=vec.end();++iter)
    {
        cout<<"333"<<endl;
        cout<<*iter<<endl;
        readerXML.parseRss(*iter);
    }
    readerXML.dump("pagelib.xml");
        cout<<"444"<<endl;
}

void PageLib::createWebLib()
{

}

void PageLib::createOffsetLib()
{

}

void PageLib::store()
{

}

}//end of namespace

