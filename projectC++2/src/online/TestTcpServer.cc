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
#include "MySimhasher.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <fstream>
#include <memory>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::unique_ptr;

int main(void)
{
    //离线部分
    wd::DirScanner dirScanner("../data/");
    dirScanner.traverse("../data/");
    wd::PageLib pagelib(dirScanner);
    pagelib.createFormatPageLib();
    pagelib.createWebLib();
	pagelib.store();
    
    unique_ptr<wd::MySimhasher> pmySimhasher (new wd::MySimhasher("./dict/jieba.dict.utf8",
                                "./dict/hmm_model.utf8",
                                "./dict/idf.utf8",
                                "./dict/stop_words.utf8"));
    pagelib.setPmySimhasher(pmySimhasher);
    pagelib.createNewLib();


    /* //测试 */
    /* ifstream ifs1("../pagelib/offset.lib"); */
    /* ifstream ifs2("../pagelib/webpage.lib"); */
    /* string lin; */ 
    /* int docid,offset,length; */
    /* int count = 0 ; */
    /* while(count<422){ */
    /*     ++count; */
    /*     getline(ifs1,lin); */
    /* } */
    /* /1* ifs1>>docid; *1/ */
    /* /1* ifs1>>offset; *1/ */
    /* /1* ifs1>>length; *1/ */
    /* ifs1>>docid>>offset>>length; */
    /* cout<<docid<<" " <<offset<<" "<<length<<endl; */
    /* char buff[65536]; */ 
    /* ifs2.seekg(offset,ifs2.beg); */
    /* ifs2.read(buff,length); */
    /* string s = buff; */
    /* cout<<buff<<endl; */
    /* cout<<s<<endl; */
    
    return 0;
}
