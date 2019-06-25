 ///
 /// @file    TestAcceptor.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-07 15:42:14
 ///
 
#include "DirScanner.h"
#include "PageLib.h"
#include "MyReaderXML.h"
#include "MySimhasher.h"
#include "MyPage.h"
#include "InvertIndex.h"

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
    wd::DirScanner dirScanner("../../data/");
    dirScanner.traverse("../../data/");
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
    
    wd::InvertIndex invertIndex;    
    invertIndex.read("../../pagelib/webpage.lib","../../pagelib/new_offset.lib");

    //测试
    /* ifstream ifs1("../../pagelib/offset.lib"); */
    /* ifstream ifs2("../../pagelib/webpage.lib"); */
    /* /1* string lin; *1/ */ 
    /* int docid,offset,length; */
    /* /1* int count = 0 ; *1/ */
    /* /1* while(count<422){ *1/ */
    /* /1*     ++count; *1/ */
    /* /1*     getline(ifs1,lin); *1/ */
    /* /1* } *1/ */
    /* /1* /2* ifs1>>docid; *2/ *1/ */
    /* /1* /2* ifs1>>offset; *2/ *1/ */
    /* /1* /2* ifs1>>length; *2/ *1/ */
    /* /1* ifs1>>docid>>offset>>length; *1/ */
    /* /1* cout<<docid<<" " <<offset<<" "<<length<<endl; *1/ */
    /* char buff[65536]; */ 
    /*  offset = 604444; */
    /*  length = 40246; */
    /* ifs2.seekg(offset,ifs2.beg); */
    /* ifs2.read(buff,length); */
    /* string s = buff; */
    /* /1* cout<<buff<<endl; *1/ */
    /* /1* cout<<s<<endl; *1/ */
    /* ifs1.close(); */
    /* ifs2.close(); */
    /* wd::MyPage mypage; */
    /* mypage.parse(s); */
    /* cout<<mypage.getDocid()<<endl; */
    /* cout<<mypage.getTitle()<<endl; */
    /* cout<<mypage.getLink()<<endl; */
    /* cout<<mypage.getDescription()<<endl; */
    /* cout<<mypage.getContent()<<endl; */
    
    return 0;
}
