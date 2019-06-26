#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>
#include <json/writer.h>

#include <stdio.h>
#include <stdlib.h>

#include "MyTask.h"
#include "MyRedis.h"
#include "Jieba.hpp"
#include "MyLibFile.h"

#include <sstream>
#include <iostream>
using std::stringstream;
using std::cout;
using std::endl;

namespace  wd
{
MyTask::MyTask(const string &msg,const TcpConnectionPtr &conn)
:_query(msg)
,_conn(conn)
{}


void MyTask::initQuery()
{
    cppjieba::Jieba jieba("./dict/jieba.dict.utf8","./dict/hmm_model.utf8","./dict/user.dict.utf8");
    jieba.Cut(_query,_words,true);
}
void MyTask::process()
{

    initQuery();
    MyLibFile * mylib = MyLibFile::getInstance();
    string webpage = mylib->getWebPageFile();
    unordered_map<int,std::pair<int,int>> offset = mylib->getOffset();
    unordered_map<string,set<std::pair<int,double>>> invert = mylib->getInvertIndex();
    
    
    //获取单例对象MyRedis
    /* MyRedis * mycli = MyRedis::getInstance(); */
    /* string resJsonStr = mycli->get(_query); */
    /* if(resJsonStr.empty()){ */
    /*     //redis缓存中没找到 */
    /* } */
    /* else */
    /* { */
    /*     //缓存中找到结果了 */
    /*     _conn->sendInLoop(resJsonStr); */
    /*     return ; */ 
    /* } */
    
    /* string res = encodeJson(); */
    /* //向redis内写入数据 */
    /* mycli->set(_query,res); */
    
    cout<<"query finish !"<<endl;
    
    _conn->sendInLoop("hello"); 
}
string MyTask::encodeJson()
{
    //返回前三个候选词
    return NULL;

}
string MyTask::decodeJson()
{
    return NULL;
}
}//end of wd

