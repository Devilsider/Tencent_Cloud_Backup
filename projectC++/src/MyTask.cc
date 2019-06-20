#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>
#include <json/writer.h>

#include <stdio.h>
#include <stdlib.h>

#include "MyTask.h"
#include "MyDict.h"

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
    {
        string tmp("");
        int len=(int )_query.size();
        for(int i=0;i<len;++i)
        {
            //对_query进行处理，只将字母取出
            if(isalpha(_query[i]))
            {
                tmp+=_query[i];
            }
        }
        _query=tmp;
    }

int MyTask::calcDistance(const string &rhs)
{
    //初始化二维数组，用于存储动态规划中的中间数值
        string s1=_query;
        string s2=rhs;

        int len1=(int)s1.size();
        int len2=(int)s2.size();
        int martix[len1+1][len2+1];
        
        for(int j=0;j<len2+1;++j)
        {
            martix[0][j]=j;
        }
        for(int i=0;i<len1+1;++i)
        {
            martix[i][0]=i;
        }
        for(int i=1;i<len1+1;++i)
        {
            for(int j=1;j<len2+1;++j)
            {
                    int f;
                    f = (s1[i-1]==s2[j-1])?0:1;
                    martix[i][j]=minOfThree(martix[i-1][j]+1,martix[i][j-1]+1,martix[i-1][j-1]+f);
            }
        }
        int res=martix[len1][len2];
        
        return res;
}

int MyTask::minOfThree(int t1,int t2,int t3)
{
    int min;
    min = t1>t2?t2:t1;
    min = min>t3?t3:min;
    return min;
}

void MyTask::process()
{
    //1.得到了索引表的指针_pindex
    //2.将单词_query与索引表中单词比对，
    //求出编辑距离，将结果存储到结构体
    //MyResult中。
    //3.设置优先级队列的比较条件，按照
    //编辑距离来比较，若编辑距离相等，则按照频次来比较，
    //频次高的在前面
    //4.取前k个单词，并将其封装成jason文件，memcpy给ms，再
    //使用sendLoop(msg),延缓到IO线程发送

    
    MyDict *mydict=MyDict::getInstance();
    vector<std::pair<string,int>> &dict = mydict->getDict();
    unordered_map<string,set<int>> &index = mydict->getIndex();
    BitMap myBitMap(100000);
    
    int len=(int)_query.size();

    
    for(int i=0;i<len;++i)
    {
        stringstream ss;
        string tmp;
        char ch=_query[i];
        ss<<ch;
        tmp=ss.str();
        auto indexSet = index.find(tmp);
        if(indexSet==index.end()){
            return;
        }
        
        
        auto & sets = indexSet->second;

        for(auto iter= sets.begin(); iter!=sets.end();++iter)
        {
            //使用BitMap去重
            if(!myBitMap.test(*iter))
            {   //未计算
                int dist = calcDistance(dict[*iter].first);
                MyResult node ;
                node._iDist=dist;
                node._iFeq=dict[*iter].second;
                node._word=dict[*iter].first;
                if(dist<=3)
                {
                    _que.push(node);
                }
                myBitMap.set(*iter);
            }
        }

    }
    //_que存入缓存,待实现
    
    string res = encodeJson();
    cout<<"query finish !"<<endl;
    
    _conn->sendInLoop(res); 
}

string MyTask::encodeJson()
{
    //返回前三个候选词
    MyResult myres;
    Json::Value root;
    Json::Value item;
    Json::Value arrayObj;
    string tmp;
    for(int idx=0;idx<3;++idx){
        if(_que.empty())
        {
            return root.toStyledString();
        }
        myres=_que.top();
        _que.pop();
        tmp="res";
        tmp.append(std::to_string(idx));
        item["_word"]=myres._word;
        item["_iDist"]=myres._iDist;
        item["_iFeq"]=myres._iFeq;
        arrayObj[tmp].append(item);
        if(_que.empty())
        {
            root.append(arrayObj) ;
            return root.toStyledString();
        }
    }
    root.append(arrayObj);
    return root.toStyledString();

}

void MyTask::clearQue()
{
    priority_queue<MyResult> empty;
    swap(empty,_que);
}

}//end of wd

