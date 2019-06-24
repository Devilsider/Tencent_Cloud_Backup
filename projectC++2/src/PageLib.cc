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
    MyReaderXML readerXML;
    auto  vec = _dirScanner.getFile();
    for(auto iter = vec.begin();iter!=vec.end();++iter)
    {
        readerXML.parseRss(*iter);
    }
    readerXML.dump("pagelib.xml");
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

