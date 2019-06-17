#include "MyTask.h"

#include <sstream>
#include <iostream>
using std::stringstream;

namespace  wd
{
MyTask::MyTask(const string &msg,const TcpConnectionPtr &conn)
:_query(msg)
,_conn(conn)
{}

int MyTask::calcDistance(string &rhs)
{
    //初始化二维数组，用于存储动态规划中的中间数值
        string s1=_query;
        string s2=rhs;

        int len1=(int)s1.size();
        int len2=(int)s2.size();

        vector<vector<int>> martix(len1+1,vector<int>(len2+1,0));
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
        return martix[len1][len2];
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
    //4.取前k个单词，并将其封装成jason文件，memcpy给msg，再
    //使用sendLoop(msg),延缓到IO线程发送
    IndexProducer * _pindex=IndexProducer::getInstance("whatever");//单例对象输入啥都行
    stringstream ss;
    string tmp;

    unordered_map<string,set<int>>& index = _pindex->getIndex();
    //process续写
    //明天写完要，不是时间不够
    for(auto &ch:_query)
    {
        //ch转换成string
        ss.clear();
        ss.str("");
        tmp.clear();
        tmp="";
        ss<<ch;
        tmp=ss.str();
        
        
        auto i= _pindex->getDict()[0];




    }
}

}//end of wd

