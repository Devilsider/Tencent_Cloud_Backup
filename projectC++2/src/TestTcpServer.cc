 ///
 /// @file    TestAcceptor.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-07 15:42:14
 ///
 
#include "Threadpool.h"
#include "DirScanner.h"
#include "PageLib.h"
#include "MyReaderXML.h"
#include "TcpServer.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

int main(void)
{
    //离线部分
    wd::DirScanner dirScanner("../data/");
    dirScanner.traverse("../data/");
    wd::PageLib pagelib(dirScanner);
    pagelib.createFormatPageLib();
    pagelib.createWebLib();
	pagelib.store();
    //测试
    ifstream ifs1("../pagelib/offset.lib");
    ifstream ifs2("../pagelib/webpage.lib");
    string lin; 
    int docid,offset,length;
    ifs1>>docid;
    ifs1>>offset;
    ifs1>>length;
    cout<<docid<<" " <<offset<<" "<<length<<endl;
    char buff[65536]; 
    ifs2.seekg(offset,ifs2.beg);
    ifs2.read(buff,length);
    string s = buff;
    cout<<buff<<endl;
    cout<<s<<endl;
    return 0;
}
