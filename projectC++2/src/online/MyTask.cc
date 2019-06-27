#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>
#include <json/writer.h>

#include <stdio.h>
#include <stdlib.h>

#include "MyTask.h"
#include "MyPage.h"
#include "MyWebPage.h"
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
    _words.erase(_words.end()-1);
}
void MyTask::process()
{
    initQuery();
    MyLibFile * mylib = MyLibFile::getInstance();
    string webpage = mylib->getWebPageFile();
    unordered_map<int,std::pair<int,int>> offset = mylib->getOffset();
    unordered_map<string,set<std::pair<int,double>>> invert = mylib->getInvertIndex();

    unordered_map<string,set<std::pair<int,double>>> web; //暂时存放同时出现这些候选词的网页
    unordered_map<string,int> worfre;//统计词频
    //可封装
    for(auto iter = _words.begin();iter!=_words.end();++iter)
    {//统计词频并查找网页set并且存入web中
        auto res = worfre.find(*iter);
        if(res==worfre.end())
        {
            //没有找到
            worfre.insert(std::make_pair(*iter,1));
        }else {
            //找到了
            ++res->second;
        }
        auto i = invert.find(*iter);
        if(i==invert.end())
        {
            //不包含该单词
            set<std::pair<int ,double>> tmpSet;//空集
            web.insert(std::make_pair(*iter,tmpSet));
        }else{
            set<std::pair<int ,double>> docidAndWei=i->second;
            web.insert(std::make_pair(*iter,docidAndWei));
        }
    }
    //计算tf-idf
    //可封装
    for(auto iter = worfre.begin();iter!=worfre.end();++iter)
    {
        double tf = iter->second;
        double N = offset.size();
    }
    




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

