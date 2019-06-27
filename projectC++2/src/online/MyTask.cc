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
#include <numeric>
#include <iostream>
#include <algorithm>
using std::stringstream;
using std::cout;
using std::endl;
using std::pair;

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
    vector<pair<string,double>> wordWeight;
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
        double idf , df,weight;
        auto resT = invert.find(iter->first);
        if(resT == invert.end()){
            df = 1;
        }
        else {
            df = resT->second.size();
        }
        idf = log(N/df);
        weight = tf * idf;
        wordWeight.push_back(std::make_pair(iter->first,weight));
    }
    //归一化处理
    double sum= 0;
    for(auto iter = wordWeight.begin();iter!=wordWeight.end();++iter)
    {
        sum += iter->second* iter->second ;
    }
    sum =sqrt(sum);
    for(auto iter = wordWeight.begin();iter!=wordWeight.end();++iter)
    {
        iter->second /= sum ;
    }

    createQueryWeb(web,wordWeight);
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
void MyTask::createQueryWeb(unordered_map<string,set<std::pair<int,double>>>&resWeb,
                            vector<std::pair<string,double>>& wordWeight)
{//先求网页交集，先将所有的docid提取出来
    unordered_map<int,vector<double>> cos;//int 为docid，vector 中依次存储wordweight的中word在该文件中的weight
    unordered_map<string,set<int>> exResWeb; 
    for(auto iter = resWeb.begin();iter!=resWeb.end();++iter)
    {
        set<int> tmp;
        auto setIter = iter->second;
        for(auto i = setIter.begin();i!=setIter.end();++i)
        {
            tmp.insert(i->first);
        }
        exResWeb.insert(std::make_pair(iter->first,tmp));
    }
    //求公共网页交集
    set<int> commonDocid;
    commonDocid = exResWeb.begin()->second;
    auto iterEx = exResWeb.begin();
    ++iterEx;
    for(;iterEx!=exResWeb.end();++iterEx)
    {
        set<int> tmpSet;
        set_intersection(commonDocid.begin(),commonDocid.end(),iterEx->second.begin(),iterEx->second.end(),
                         inserter(tmpSet,tmpSet.begin()));
        swap(commonDocid,tmpSet);
    }
    for(auto ite = commonDocid.begin();ite!=commonDocid.end();++ite)
    {
        vector<double> tmp;
        for(auto it = wordWeight.begin();it!=wordWeight.end();++it)
        {
            auto res = resWeb.find(it->first);
            
            for(auto &c:res->second)
            {
                if(c.first==*ite){
                    tmp.push_back(c.second);
                }
            }
        }
        cos.insert(std::make_pair(*ite,tmp));
    }
    //计算余弦相似度 
    //将候选单词的weight提取出来
    vector<double> v2;
    for(auto iter=wordWeight.begin();iter!=wordWeight.end();++iter)
    {
        v2.push_back(iter->second);
    }
    for(auto iter=cos.begin();iter!=cos.end();++iter)
    {
        auto v1 = iter->second;
        double res = calCos(v1,v2);
        MyNode node;
        node._docid=iter->first;
        node._cos = res;
        _resQue.push(node);
    }
    while(_resQue.size()!=0) {
        MyNode node = _resQue.top();
        cout<<node._docid<<" "<<node._cos<<endl;
        _resQue.pop();
    }
    cout<<endl;

}
double MyTask::calCos(vector<double> &v1,vector<double> &v2)
{
    double inner = inner_product(v1.begin(),v1.end(),v2.begin(),0.0);
    double sumV1=0;
    double sumV2=0;
    for(int idx=0;idx<(int)v1.size();++idx)
    {
        sumV1 += v1[idx]*v1[idx];
        sumV2 += v2[idx]*v2[idx];
    }
    sumV1 = sqrt(sumV1);
    sumV2 = sqrt(sumV2);

    double cos = inner/(sumV1*sumV2);
    return cos;
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

